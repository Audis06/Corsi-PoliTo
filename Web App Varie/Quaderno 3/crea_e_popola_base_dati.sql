SET storage_engine=InnoDB;
CREATE DATABASE IF NOT EXISTS QUADERNO3;
SET FOREIGN_KEY_CHECKS=1;

USE QUADERNO3;  

DROP TABLE IF EXISTS PERSONA;
DROP TABLE IF EXISTS PODCAST;
DROP TABLE IF EXISTS INFO_PODCAST;
DROP TABLE IF EXISTS APPARIZIONE;

-- Creazione della tabella PERSONA
CREATE TABLE PERSONA (
    CodiceFiscale CHAR(16) PRIMARY KEY,
    Nome CHAR(255),
    Cognome CHAR(255),
    Nazione CHAR(255),
    Età INT
);

-- Creazione della tabella PODCAST
CREATE TABLE PODCAST (
    CodPodcast CHAR(10),
    CodFiscalePresentatore CHAR(16),
    PRIMARY KEY(CodPodcast, CodFiscalePresentatore)
);

-- Creazione della tabella INFO_PODCAST
CREATE TABLE INFO_PODCAST (
    CodPodcast CHAR(10),
    Titolo CHAR(255),
    Servizio CHAR(255),
    Finito BOOLEAN,
    PRIMARY KEY (CodPodcast, Titolo)
);

-- Creazione della tabella APPARIZIONE
CREATE TABLE APPARIZIONE (
    CodiceFiscalePartecipante CHAR(16),
    CodPodcast CHAR(10),
    NumeroPuntata INT,
    DataUscita DATE,
    PRIMARY KEY (CodiceFiscalePartecipante, CodPodcast, NumeroPuntata),
    FOREIGN KEY (CodPodcast)
        REFERENCES PODCAST (CodPodcast)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

-- Popolamento della tabella PERSONA
INSERT INTO PERSONA (CodiceFiscale, Nome, Cognome, Nazione, Età)
VALUES
    ('CF001', 'Mario', 'Rossi', 'Italia', 30),
    ('CF002', 'Anna', 'Bianchi', 'Italia', 25),
    ('CF003', 'Luca', 'Verdi', 'Spagna', 35),
    ('CF004', 'Elena', 'Neri', 'Francia', 28),
    ('CF005', 'Fabio', 'Musso', 'Peru', 23);

-- Popolamento della tabella PODCAST
INSERT INTO PODCAST (CodPodcast, CodFiscalePresentatore)
VALUES
    ('PODCAST001', 'CF001'),
    ('PODCAST002', 'CF003'),
    ('PODCAST003', 'CF002');

-- Popolamento della tabella INFO_PODCAST
INSERT INTO INFO_PODCAST (CodPodcast, Titolo, Servizio, Finito)
VALUES
    ('PODCAST001', 'Muschio Selvaggio', 'Servizio1', true),
    ('PODCAST002', 'BoboTv', 'Servizio2', false),
    ('PODCAST003', 'Deskonectados', 'Servizio3', true);

-- Popolamento della tabella APPARIZIONE
INSERT INTO APPARIZIONE (CodiceFiscalePartecipante, CodPodcast, NumeroPuntata, DataUscita)
VALUES
    ('CF002', 'PODCAST001', 10, '2023-11-01'),
    ('CF003', 'PODCAST001', 12, '2023-11-05'),
    ('CF001', 'PODCAST002', 5, '2023-11-10'),
    ('CF004', 'PODCAST003', 8, '2023-11-15');


