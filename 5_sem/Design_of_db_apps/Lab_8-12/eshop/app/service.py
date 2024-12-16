from domain.repositories import ProductRepository, CartRepository, OrderRepository


class ProductService:
    def __init__(self, product_repository):
        self.product_repository = product_repository

    def get_all_products(self):
        # For now, return fake data
        return [
            {
                "id": 1,
                "name": "Laptop",
                "price": 1200,
                "description": "High-end laptop",
            },
            {
                "id": 2,
                "name": "Smartphone",
                "price": 800,
                "description": "Latest model smartphone",
            },
        ]

    def get_product_details(self, product_id):
        # Fake product detail
        return {
            "id": product_id,
            "name": "Laptop",
            "price": 1200,
            "description": "High-end laptop",
        }

    def create_product(self, name, price, description):
        # Example logic to create a product
        new_product = Product(name=name, price=price, description=description)
        self.product_repository.save(new_product)
        return new_product

    def update_product(self, product_id, name, price, description):
        product = self.product_repository.get_by_id(product_id)
        if not product:
            raise ValueError("Product not found")
        product.name = name
        product.price = price
        product.description = description
        self.product_repository.save(product)

    def delete_product(self, product_id):
        self.product_repository.delete(product_id)


class CartService:
    def __init__(self, cart_repository):
        self.cart_repository = cart_repository

    def get_cart_content(self, cart_id):
        # Fake cart content
        return {
            "cart_id": cart_id,
            "products": [
                {"id": 1, "name": "Laptop", "price": 1200, "quantity": 1},
                {"id": 2, "name": "Smartphone", "price": 800, "quantity": 2},
            ],
        }

    def add_product_to_cart(self, cart_id, product_id, quantity):
        cart = self.cart_repository.get_by_id(cart_id)
        if not cart:
            raise ValueError("Cart not found")
        cart.add_product(product_id, quantity)
        self.cart_repository.save(cart)

    def remove_product_from_cart(self, cart_id, product_id):
        cart = self.cart_repository.get_by_id(cart_id)
        if not cart:
            raise ValueError("Cart not found")
        cart.remove_product(product_id)
        self.cart_repository.save(cart)

    def clear_cart(self, cart_id):
        cart = self.cart_repository.get_by_id(cart_id)
        if not cart:
            raise ValueError("Cart not found")
        cart.clear()
        self.cart_repository.save(cart)


class OrderService:
    def __init__(self, order_repository):
        self.order_repository = order_repository

    def create_order(self, cart_id, address):
        # Convert cart to an order (fake logic for now)
        order = {
            "order_id": 1,
            "cart_id": cart_id,
            "address": address,
            "status": "Created",
        }
        self.order_repository.save(order)
        return order

    def get_order_details(self, order_id):
        return {"order_id": order_id, "status": "Created", "address": "123 Main St"}


product_service = ProductService(ProductRepository())
