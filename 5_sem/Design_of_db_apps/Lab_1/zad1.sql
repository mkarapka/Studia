SELECT "City"
FROM SalesLT.Address
         Inner Join SalesLT.SalesOrderHeader
                    ON SalesLT.SalesOrderHeader.ShipToAddressID =
                       SalesLT.Address.AddressID
GROUP BY City
ORDER BY 1
