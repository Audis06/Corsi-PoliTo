-- Creazione della base dati

SET storage_engine=InnoDB;
CREATE DATABASE IF NOT EXISTS BIBLIOTECA;
SET FOREIGN_KEY_CHECKS=1;

USE BIBLIOTECA;  

DROP TABLE IF EXISTS PRESTITI;
DROP TABLE IF EXISTS MEMBRI;
DROP TABLE IF EXISTS LIBRI;



-- Creazione della tabella LIBRI
CREATE TABLE LIBRI (
    ISBN VARCHAR(13) PRIMARY KEY,
    Titolo VARCHAR(255) NOT NULL,
    Autore VARCHAR(255) NOT NULL,
    Editore VARCHAR(255) NOT NULL,
    Anno YEAR NOT NULL,
    Genere VARCHAR(100) NOT NULL
);

-- Creazione della tabella MEMBRI
CREATE TABLE MEMBRI (
    CodFisc CHAR(16) PRIMARY KEY,
    Nome VARCHAR(100) NOT NULL,
    Cognome VARCHAR(100) NOT NULL,
    DataNascita DATE NOT NULL,
    Email VARCHAR(255) NOT NULL UNIQUE,
    Telefono VARCHAR(15) -- Campo opzionale
);

-- Creazione della tabella PRESTITI
CREATE TABLE PRESTITI (
    ISBN VARCHAR(13),
    DataPrestito DATE NOT NULL,
    CodFisc CHAR(16),
    DataRestituzione DATE NOT NULL,
    PRIMARY KEY (ISBN, DataPrestito, CodFisc),
    FOREIGN KEY (ISBN) REFERENCES LIBRI(ISBN),
    FOREIGN KEY (CodFisc) REFERENCES MEMBRI(CodFisc),
    CHECK (DataRestituzione >= DataPrestito)
);


-- Tabella LIBRI: aggiunte nuove righe
INSERT INTO LIBRI (ISBN, Titolo, Autore, Editore, Anno, Genere)
VALUES
    ('9780131103627', 'Il Richiamo della Foresta', 'Jack London', 'Mondadori', 2020, 'Avventura'),
    ('9780747532743', 'Harry Potter e la Pietra Filosofale', 'J.K. Rowling', 'Salani', 1997, 'Fantasy'),
    ('9780345816023', 'Il Racconto della Ancella', 'Margaret Atwood', 'Ponte alle Grazie', 2019, 'Distopico'),
    ('9788804670515', 'Il Nome della Rosa', 'Umberto Eco', 'Bompiani', 1980, 'Giallo'),
    ('9788807890170', 'Le Città Invisibili', 'Italo Calvino', 'Mondadori', 1972, 'Filosofia'),
    ('9781408855652', 'Harry Potter e la Camera dei Segreti', 'J.K. Rowling', 'Salani', 1998, 'Fantasy'),
    ('9788804729336', 'Sapiens: Da Animali a Dei', 'Yuval Noah Harari', 'Bompiani', 2017, 'Saggistica'),
    ('9788804715599', 'Don Chisciotte della Mancia', 'Miguel de Cervantes', 'Einaudi', 2021, 'Classico'),
    ('9780399590504', 'Becoming', 'Michelle Obama', 'Crown', 2018, 'Autobiografia'),
    ('9781982131739', 'Educated', 'Tara Westover', 'Random House', 2018, 'Memoria'),
    ('9781501161933', 'The Great Alone', 'Kristin Hannah', 'St. Martin s Press', 2018, 'Narrativa'),
    ('9780345538376', 'The Goldfinch', 'Donna Tartt', 'Little, Brown', 2013, 'Narrativa'),
    ('9780679783275', 'Pride and Prejudice', 'Jane Austen', 'Vintage', 1813, 'Classico'),
    ('9780062457714', 'The Subtle Art of Not Giving a F*ck', 'Mark Manson', 'HarperOne', 2016, 'Saggistica'),
    ('9780385472579', 'The Alchemist', 'Paulo Coelho', 'HarperCollins', 1993, 'Filosofia'),
    ('9780451524935', '1984', 'George Orwell', 'Signet Classics', 1949, 'Distopico');

-- Tabella MEMBRI: aggiunte nuove righe
INSERT INTO MEMBRI (CodFisc, Nome, Cognome, DataNascita, Email, Telefono)
VALUES
    ('RSSMRA85M01H501Z', 'Mario', 'Rossi', '1985-03-01', 'mario.rossi@example.com', '1234567890'),
    ('BNCGLC92D15A001B', 'Alice', 'Bianchi', '1992-04-15', 'alice.bianchi@example.com', NULL),
    ('VRDLGI99M20C345T', 'Luigi', 'Verdi', '1999-07-20', 'luigi.verdi@example.com', '0987654321'),
    ('CNTFBA80F01H245L', 'Fabiana', 'Conti', '1980-11-01', 'fabiana.conti@example.com', NULL),
    ('PLLMNL88C31D876W', 'Manuela', 'Pellegrini', '1988-12-31', 'manuela.pellegrini@example.com', '3456789012'),
    ('MRTFRN95D15G456Y', 'Franco', 'Martini', '1995-04-15', 'franco.martini@example.com', '4567890123'),
    ('ZNTLRA93A05G765L', 'Laura', 'Zanetti', '1993-01-05', 'laura.zanetti@example.com', '6789012345'),
    ('BRBGTR86L20M023K', 'Giorgio', 'Barbagallo', '1986-12-20', 'giorgio.barbagallo@example.com', NULL),
    ('CLDMNL85D30C123M', 'Daniela', 'Colombo', '1985-04-30', 'daniela.colombo@example.com', '7890123456'),
    ('VLLFRS90B01F245P', 'Francesco', 'Valli', '1990-02-01', 'francesco.valli@example.com', '8901234567'),
    ('RSNRLM97C11D432T', 'Arianna', 'Rossi', '1997-03-11', 'arianna.rossi@example.com', NULL),
    ('BLGLSN89E25F321Q', 'Alessandro', 'Bulgari', '1989-05-25', 'alessandro.bulgari@example.com', '9123456780');

-- Tabella PRESTITI: aggiunte nuove righe
INSERT INTO PRESTITI (ISBN, DataPrestito, CodFisc, DataRestituzione)
VALUES
    ('9780131103627', '2024-11-01', 'RSSMRA85M01H501Z', '2024-11-15'),
    ('9780747532743', '2024-11-05', 'BNCGLC92D15A001B', '2024-11-20'),
    ('9780345816023', '2024-10-15', 'VRDLGI99M20C345T', '2024-11-01'),
    ('9788804729336', '2024-09-01', 'MRTFRN95D15G456Y', '2024-09-20'),
    ('9788804715599', '2024-09-15', 'BNCGLC92D15A001B', '2024-10-01'),
    ('9781408855652', '2024-08-01', 'RSSMRA85M01H501Z', '2024-08-20'),
    ('9780399590504', '2024-11-01', 'ZNTLRA93A05G765L', '2024-11-20'),
    ('9781501161933', '2024-10-12', 'CLDMNL85D30C123M', '2024-10-30'),
    ('9780679783275', '2024-11-10', 'RSNRLM97C11D432T', '2024-11-25'),
    ('9780062457714', '2024-10-15', 'BLGLSN89E25F321Q', '2024-10-31'),
    ('9780385472579', '2024-09-20', 'CNTFBA80F01H245L', '2024-10-10'),
    ('9780451524935', '2024-08-30', 'MRTFRN95D15G456Y', '2024-09-15');

