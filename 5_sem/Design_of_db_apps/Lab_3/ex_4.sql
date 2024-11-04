CREATE TRIGGER trg_UpdateModifiedDate
ON SalesLT.Customer
AFTER UPDATE
AS
BEGIN
    UPDATE SalesLT.Customer
    SET ModifiedDate = GETDATE()
    WHERE CustomerID IN (SELECT DISTINCT CustomerID FROM Inserted);
END;
GO