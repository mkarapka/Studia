// 1
/**
 * @typedef {object} Product
 * @property {number} id - product id
 * @property {string} name - product name
 * @property {number} quantity - product quantity
 * @property {Date} purchaseDate
 * @property {boolean} isPurchased
 * @property {number} [price] - Unit price
*/

// 2
/** @type {Product[]} */
let shoppinglist = [];


// 3
/**
 * Adding new product to shopping list
 * @param {string} name 
 * @param {number} quantity 
 * @param {string} purchaseDateStr 
 */
function addProduct(name, quantity, purchaseDateStr) {
    const id = Math.floor(Math.random() * 100_000)
    const purchaseDate = new Date(purchaseDateStr)
    shoppinglist.push({ id, name, quantity, purchaseDate, isPurchased: false });
}


// 4
/**
 * Removing product from shopping list based on id
 * @param {number} id 
 */
function removeProduct(id) {
    shoppinglist = shoppinglist.filter(p => p.id !== id);
}


// 5.1
/**
 * Editing a product name based on id
 * @param {number} id 
 * @param {string} name 
 */
function editProductName(id, name) {
    const product = shoppinglist.find(p => p.id === id);
    if (product) product.name = name;
}


// 5.2
/**
 * Editing a product quantity based on id
 * @param {number} id 
 * @param {number} quantity 
 */
function editProductQuantity(id, quantity) {
    const product = shoppinglist.find(p => p.id === id);
    if (product) product.quantity = quantity;
}

//5.3
/**
 * Editing a product date based on id
 * @param {number} id 
 * @param {string} dateStr 
 */
function editProductDate(id, dateStr) {
    const product = shoppinglist.find(p => p.id === id);
    if (product) product.purchaseDate = new Date(dateStr);
}

// 5.4
/**
 * Editing a product status based on id
 * @param {*} id 
 * @param {*} newStatus 
 */
function editProductStatus(id, newStatus) {
    const product = shoppinglist.find(product => product.id === id);
    if (product) product.isPurchased = newStatus;
}

// 6
/**
 * Switching a product order by moving up
 * @param {number} id 
 * @returns {string|undefined} - Returns a message if the product cannot be moved, otherwise undefined.
 */
function moveProduct(id) {
    const index = shoppinglist.findIndex(p => p.id === id);
    if (index === -1) return;
    if (index === shoppinglist.length - 1) return "Cannot move the product because it is already the last item in the shopping list.";
    const [product] = shoppinglist.splice(index, 1)
    shoppinglist.splice(index+1, 0, product)
}

// 7
/**
 * Return list of products to buy today
 * @returns {Product[]} - Returns an array of products that need to be purchased today.
 */
function getTodaysPurchases(){
    const today = new Date().toDateString();
    return shoppinglist.filter(p => p.purchaseDate.toDateString() === today && !p.isPurchased);
}


// 8
/**
 * Setting the product price
 * @param {number} id 
 * @param {number} price 
 */
function setProductPrice(id, price){
    const product = shoppinglist.find(p => p.id === id);
    if (product) product.price = price;
}


// 9
/**
 * Calculating cost of purchased product particular day
 * @param {string} dateStr 
 * @returns {Product[]} - Returns an array of products that need to be purchased today.
 */
function calculateDailyExpense(dateStr){
    const date = new Date(dateStr).toDateString();
    return shoppinglist.reduce((total, product) => {
        if (product.isPurchased && product.purchaseDate.toDateString() === date && product.price !== undefined){
            return total + product.quantity * product.price;   
    }
    return total;
}, 0);
}

/**
 * Formatting shopping list by given function
 * @param {*} ids 
 * @param {*} modifyFunction 
 */
function bulkModifyProducts(ids, modifyFunction){
    shoppinglist.forEach(p => {
        if(ids.includes(p.id)) {
            modifyFunction(p);
        }
    });
}

function editProductStatus(id, newStatus) {
    const product = shoppinglist.find(product => product.id === id);
    if (product) product.isPurchased = newStatus;
}


// Examples
addProduct("Milk", 2, "2025-04-02");
addProduct("Bread", 1, "2025-04-02");
console.log("Shopping list", shoppinglist)

// 1
const firstId = shoppinglist[0].id;
editProductName(firstId, "Chocolate Milk")
editProductDate(firstId, "2025-04-04");
editProductQuantity(firstId, 4);
console.log("After first edit:", shoppinglist)

// 2
moveProduct(firstId)
console.log("After moved: ", shoppinglist)

// 3
removeProduct(firstId);
console.log("After remove", shoppinglist);

// 4
addProduct("Eggs", 12, "2025-04-04");
addProduct("Butter", 1, "2025-04-04");
const bId = shoppinglist[2].id;
const eId = shoppinglist[1].id;
setProductPrice(bId, 4);
setProductPrice(eId, 1);
editProductStatus(bId, true);
editProductStatus(eId, true);
console.log(shoppinglist)

// 5
const expense = calculateDailyExpense("2025-04-04");
console.log(`Total expense for 2025-04-02: ${expense}`);

// 6
console.log("Products to buy today:");
console.log(getTodaysPurchases());

// 7
const idsToModify = shoppinglist.map(p => p.id); 
bulkModifyProducts(idsToModify, product => {
    product.isPurchased = true; 
});
console.log("Shopping list after bulk modification:");
console.log(shoppinglist);