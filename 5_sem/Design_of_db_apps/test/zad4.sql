-- INSERT INTO [SalesLT].[ProductCategory] (Name, ParentProductCategoryID) VALUES ('MTB600', 5)
-- INSERT INTO [SalesLT].[Product] (Name, ProductCategoryID, ProductNumber, StandardCost, ListPrice, SellStartDate) VALUES ('MTB600 bike product', 42, 'MTB-600', 1000.00, 1500.00, '2014-02-01')

SELECT c.Name, p.Name
FROM SalesLT.Product p, SalesLT.ProductCategory c
WHERE c.ProductCategoryID = c.ProductCategoryID
    AND c.ProductCategoryID IN 
(SELECT DISTINCT ParentProductCategoryID
    FROM SalesLT.ProductCategory
    WHERE ParentProductCategoryID IS NOT NULL);
