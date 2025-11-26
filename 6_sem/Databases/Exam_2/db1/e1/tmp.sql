BEGIN;

-- Usunięcie istniejących ograniczeń kluczy obcych
ALTER TABLE offer DROP CONSTRAINT IF EXISTS offer_company_id_fkey;
ALTER TABLE employment_details DROP CONSTRAINT IF EXISTS employment_details_offer_id_fkey;
ALTER TABLE skill DROP CONSTRAINT IF EXISTS skill_offer_id_fkey;

-- Odtworzenie z kaskadowym usuwaniem
ALTER TABLE offer 
    ADD CONSTRAINT offer_company_id_fkey 
    FOREIGN KEY (company_id) REFERENCES company(id) 
    ON DELETE CASCADE;
    
ALTER TABLE employment_details 
    ADD CONSTRAINT employment_details_offer_id_fkey 
    FOREIGN KEY (offer_id) REFERENCES offer(id) 
    ON DELETE CASCADE;
    
ALTER TABLE skill 
    ADD CONSTRAINT skill_offer_id_fkey 
    FOREIGN KEY (offer_id) REFERENCES offer(id) 
    ON DELETE CASCADE;

DELETE FROM company
WHERE id IN (
    SELECT company_id
    FROM offer
    GROUP BY company_id
    HAVING COUNT(*) > 200
);
ROLLBACK;

