// Challange 1
console.log("Challange 1")
/*
console.log(capitalize("alice"));

const capitalize = (str) => {
  return str.charAt(0).toUpperCase() + str.slice(1);
};
*/


console.log(capitalize("alice"));

function capitalize(str) {
  return str.charAt(0).toUpperCase() + str.slice(1);
}

// Challange 2 
console.log("Challange 2")
function capitalizeSentence(sentence) {
    return sentence
      .split(" ")
      .map(word => capitalize(word))
      .join(" ");
  }
  
  // Test
  console.log(capitalizeSentence("alice")); // Alice
  console.log(capitalizeSentence("alice in wonderland")); // Alice In Wonderland

  
// Challange 3
console.log("Challange 3")

/*
const ids = [];

const generateId = () => {
  let id = 0;

  do {
    id++;
  } while (ids.includes(id));

  ids.push(id);
  return id;
};
*/

const ids = new Set();

const generateId = () => {
  let id = 0;

  do {
    id++;
  } while (ids.has(id));

  ids.add(id);
  return id;
};

// Test wydajności
console.time("generateId");

for (let i = 0; i < 3000; i++) {
  generateId();
}

console.timeEnd("generateId");

// Challange 4
console.log("Challange 4")
    function compareObjects(obj1, obj2) {
        if (typeof obj1 !== typeof obj2) return false;
    
        if (typeof obj1 !== "object" || obj1 === null || obj2 === null) {
        return obj1 === obj2;
        }
  
    const keys1 = Object.keys(obj1);
    const keys2 = Object.keys(obj2);
  
    if (keys1.length !== keys2.length) return false;
  
    for (let key of keys1) {
      if (!keys2.includes(key)) return false;
      if (!compareObjects(obj1[key], obj2[key])) return false;
    }
  
    return true;
  }

  const obj1 = {
    name: "Alice",
    age: 25,
    address: {
      city: "Wonderland",
      country: "Fantasy",
    },
  };
  
  const obj2 = {
    name: "Alice",
    age: 25,
    address: {
      city: "Wonderland",
      country: "Fantasy",
    },
  };
  
  const obj3 = {
    age: 25,
    address: {
      city: "Wonderland",
      country: "Fantasy",
    },
    name: "Alice",
  };
  
  const obj4 = {
    name: "Alice",
    age: 25,
    address: {
      city: "Not Wonderland",
      country: "Fantasy",
    },
  };
  
  const obj5 = {
    name: "Alice",
  };
  
  console.log("Should be True:", compareObjects(obj1, obj2));
  console.log("Should be True:", compareObjects(obj1, obj3));
  console.log("Should be False:", compareObjects(obj1, obj4));
  console.log("Should be True:", compareObjects(obj2, obj3));
  console.log("Should be False:", compareObjects(obj2, obj4));
  console.log("Should be False:", compareObjects(obj3, obj4));
  console.log("Should be False:", compareObjects(obj1, obj5));
  console.log("Should be False:", compareObjects(obj5, obj1));

// Challange 5
let library = [];

const addBookToLibrary = (title, author, pages, isAvailable, ratings) => {
  if (typeof title !== "string" || title.trim() === "") {
    throw new Error("Invalid title");
  }

  if (typeof author !== "string" || author.trim() === "") {
    throw new Error("Invalid author");
  }

  if (typeof pages !== "number" || pages <= 0) {
    throw new Error("Invalid pages");
  }

  if (typeof isAvailable !== "boolean") {
    throw new Error("Invalid availability flag");
  }

  if (!Array.isArray(ratings) || !ratings.every(r => typeof r === "number" && r >= 0 && r <= 5)) {
    throw new Error("Invalid ratings");
  }

  library.push({
    title,
    author,
    pages,
    available: isAvailable,
    ratings,
  });
};

// Challange 6 
console.log("Challange 6")
function testAddingBooks(testCases) {
    for (const { testCase, shouldFail } of testCases) {
      try {
        addBookToLibrary(...testCase);
        if (shouldFail) {
          console.log("Test failed:", testCase);
        } else {
          console.log("Test passed:", testCase);
        }
      } catch (err) {
        if (shouldFail) {
          console.log("Test passed:", testCase, "Error:", err.message);
        } else {
          console.log("Test failed:", testCase, "Error:", err.message);
        }
      }
    }
  }
  
  // Test cases
  const testCases = [
    { testCase: ["", "Author", 200, true, []], shouldFail: true },
    { testCase: ["Title", "", 200, true, []], shouldFail: true },
    { testCase: ["Title", "Author", -1, true, []], shouldFail: true },
    { testCase: ["Title", "Author", 200, "yes", []], shouldFail: true },
    { testCase: ["Title", "Author", 200, true, [1, 2, 3, 6]], shouldFail: true },
    {
      testCase: ["Title", "Author", 200, true, [1, 2, 3, "yes"]],
      shouldFail: true,
    },
    { testCase: ["Title", "Author", 200, true, [1, 2, 3, {}]], shouldFail: true },
    { testCase: ["Title", "Author", 200, true, []], shouldFail: false },
    { testCase: ["Title", "Author", 200, true, [1, 2, 3]], shouldFail: false },
    { testCase: ["Title", "Author", 200, true, [1, 2, 3, 4]], shouldFail: false },
    {
      testCase: ["Title", "Author", 200, true, [1, 2, 3, 4, 5]],
      shouldFail: false,
    },
    {
      testCase: ["Title", "Author", 200, true, [1, 2, 3, 4, 5]],
      shouldFail: false,
    },
  ];
  
  testAddingBooks(testCases);

// Challange 7 
console.log("Challange 7")
function addBooksToLibrary(books) {
    books.forEach(args => {
      addBookToLibrary(...args);
    });
  }
  
  // Test
  const books = [
    ["Alice in Wonderland", "Lewis Carroll", 200, true, [1, 2, 3]],
    ["1984", "George Orwell", 300, true, [4, 5]],
    ["The Great Gatsby", "F. Scott Fitzgerald", 150, true, [3, 4]],
    ["To Kill a Mockingbird", "Harper Lee", 250, true, [2, 3]],
    ["The Catcher in the Rye", "J.D. Salinger", 200, true, [1, 2]],
    ["The Hobbit", "J.R.R. Tolkien", 300, true, [4, 5]],
    ["Fahrenheit 451", "Ray Bradbury", 200, true, [3, 4]],
    ["Brave New World", "Aldous Huxley", 250, true, [2, 3]],
    ["The Alchemist", "Paulo Coelho", 200, true, [1, 2]],
    ["The Picture of Dorian Gray", "Oscar Wilde", 300, true, [4, 5]],
  ];
  
  addBooksToLibrary(books);
  console.log(library);
  