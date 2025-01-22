from abc import ABC, abstractmethod
from typing import List
from uuid import UUID
<<<<<<< HEAD
from .entities.entities import Cart, Order, Product
=======
from entities.entities import Cart, Order, Product
>>>>>>> c343c1f6412df2165447dc3023bcdf64e0400d51


class ProductRepository(ABC):
    @abstractmethod
    def get(self, product_id: UUID) -> Product:
        pass

    @abstractmethod
    def get_all(self) -> List[Product]:
        pass

    @abstractmethod
    def add(self, product: Product):
        pass

    @abstractmethod
    def update(self, product: Product):
        pass

    @abstractmethod
    def delete(self, product_id: UUID):
        pass


class CartRepository(ABC):
    @abstractmethod
    def get(self, cart_id: UUID) -> Cart:
        pass

    @abstractmethod
    def add(self, cart: Cart):
        pass

    @abstractmethod
    def update(self, cart: Cart):
        pass

    @abstractmethod
    def delete(self, cart_id: UUID):
        pass


class OrderRepository(ABC):
    @abstractmethod
    def get(self, order_id: UUID) -> Order:
        pass

    @abstractmethod
    def add(self, order: Order):
        pass

    @abstractmethod
    def update(self, order: Order):
        pass

    @abstractmethod
    def delete(self, order_id: UUID):
        pass
