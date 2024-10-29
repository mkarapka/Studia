SELECT pm.Name, COUNT(*) amt
FROM [SalesLT].[Product] p LEFT JOIN [SalesLT].[ProductModel] pm ON p.ProductModelID = pm.ProductModelID
GROUP BY pm.ProductModelID, pm.Name
HAVING COUNT(*) > 1

-- Gdybyśmy grupowali tylko ze względu na pm.Name
-- Mogła by być taka sytuacja, że byłyby 2 inne produkty z tą samą nazwą 
-- Więc zostałby zgrupowane
