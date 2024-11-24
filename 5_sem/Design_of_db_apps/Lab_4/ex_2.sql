USE AdventureWorksLT;  
GO

IF EXISTS (SELECT name
FROM sys.objects
WHERE name = N'SaveTranExample_UpdateEmail')  
    DROP PROCEDURE SaveTranExample_UpdateEmail;  
GO

CREATE PROCEDURE SaveTranExample_UpdateEmail
    @EmployeeID INT,
    @NewEmail NVARCHAR(50)
AS
DECLARE @TranCounter INT;
SET @TranCounter = @@TRANCOUNT;

IF @TranCounter > 0  
        SAVE TRANSACTION ProcedureSave;  
    ELSE  
        BEGIN TRANSACTION;

BEGIN TRY  
        UPDATE HumanResources.Employee  
        SET EmailAddress = @NewEmail  
        WHERE BusinessEntityID = @EmployeeID;  

        IF @TranCounter = 0  
            COMMIT TRANSACTION;  

    END TRY  
    BEGIN CATCH  
        IF @TranCounter = 0  
            ROLLBACK TRANSACTION;  
        ELSE  
            IF XACT_STATE() <> -1  
                ROLLBACK TRANSACTION ProcedureSave;  

        DECLARE @ErrorMessage NVARCHAR(4000);  
        DECLARE @ErrorSeverity INT;  
        DECLARE @ErrorState INT;  
  
        SELECT @ErrorMessage = ERROR_MESSAGE();  
        SELECT @ErrorSeverity = ERROR_SEVERITY();  
        SELECT @ErrorState = ERROR_STATE();  
  
        RAISERROR (@ErrorMessage, @ErrorSeverity, @ErrorState);  
    END CATCH  
GO  