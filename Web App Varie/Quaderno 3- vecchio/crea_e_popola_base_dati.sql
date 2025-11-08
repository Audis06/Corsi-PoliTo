SET storage_engine=InnoDB;
CREATE DATABASE IF NOT EXISTS QUADERNO3;
SET FOREIGN_KEY_CHECKS=1;

USE QUADERNO3;  

DROP TABLE IF EXISTS CHEF;
DROP TABLE IF EXISTS PROGRAMMATV;
DROP TABLE IF EXISTS APPARIZIONE;

CREATE TABLE CHEF(
    CodiceFiscaleChef CHAR(20),
    Nome CHAR(50) NOT NULL,
    Cognome CHAR(50) NOT NULL,
    Nazione CHAR(50) NOT NULL,
    età INTEGER NOT NULL,
    PRIMARY KEY (CodiceFiscaleChef)
);

CREATE TABLE PROGRAMMATV(
    CodProgramma CHAR(3) NOT NULL,
    Titolo CHAR(50) NOT NULL,
    CanaleTV CHAR(50) NOT NULL, 
    Editore CHAR(50) NOT NULL,
    PRIMARY KEY (CodProgramma)
    );


CREATE TABLE APPARIZIONE(
    CodiceFiscaleChef CHAR(20),
    CodProgramma CHAR(3),
    NumeroPuntata INTEGER NOT NULL,
    Data DATE NOT NULL,
    OraInizio CHAR(20) NOT NULL,
    OraFine CHAR(20) NOT NULL,
    PRIMARY KEY (CodiceFiscaleChef,CodProgramma,Data,OraInizio),
    FOREIGN KEY (CodiceFiscaleChef)
        REFERENCES CHEF (CodiceFiscaleChef)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (CodProgramma)
        REFERENCES PROGRAMMATV (CodProgramma)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

insert into CHEF (CodiceFiscaleChef, Nome, Cognome, Nazione, età) values ('C01', 'Boone', 'Badrick', 'Italia', 35);
insert into CHEF (CodiceFiscaleChef, Nome, Cognome, Nazione, età) values ('C02', 'Harmonia', 'Allmark', 'Spagna', 40);
insert into CHEF (CodiceFiscaleChef, Nome, Cognome, Nazione, età) values ('C03', 'Elden', 'Musgrove', 'Inghilterra', 25);
insert into CHEF (CodiceFiscaleChef, Nome, Cognome, Nazione, età) values ('C04', 'Catarina', 'Forri', 'Perù', 26);
insert into CHEF (CodiceFiscaleChef, Nome, Cognome, Nazione, età) values ('C05', 'Cassandre', 'Whellans', 'Germania', 56);
insert into CHEF (CodiceFiscaleChef, Nome, Cognome, Nazione, età) values ('C06', 'Enoch', 'Denzey', 'Francia', 30);
insert into CHEF (CodiceFiscaleChef, Nome, Cognome, Nazione, età) values ('C07', 'Carmel', 'Canwell', 'Italia', 28);
insert into CHEF (CodiceFiscaleChef, Nome, Cognome, Nazione, età) values ('C08', 'Bradley', 'Prattin', 'Argentina', 39);
insert into CHEF (CodiceFiscaleChef, Nome, Cognome, Nazione, età) values ('C09', 'Willyt', 'Legendre', 'Brasile', 41);
insert into CHEF (CodiceFiscaleChef, Nome, Cognome, Nazione, età) values ('C10', 'Friederike', 'Kearton', 'Portogallo', 45);

insert into PROGRAMMATV (Codprogramma, Titolo, CanaleTV, Editore) values ('P01', 'MasterChef', 'MTV', 'Endemol Shine Italy');
insert into PROGRAMMATV (Codprogramma, Titolo, CanaleTV, Editore) values ('P02', 'La Prova del Cuoco', 'DMAX', 'Albatross Entertainment');
insert into PROGRAMMATV (Codprogramma, Titolo, CanaleTV, Editore) values ('P03', 'Cucina da Incubo', 'La7', 'Ballandi Arts');
insert into PROGRAMMATV (Codprogramma, Titolo, CanaleTV, Editore) values ('P04', 'Bake off', 'MTV', 'SD Cinematografica');
insert into PROGRAMMATV (Codprogramma, Titolo, CanaleTV, Editore) values ('P05', 'I menu di Benedetta', 'MTV', 'Mediavivere');
insert into PROGRAMMATV (Codprogramma, Titolo, CanaleTV, Editore) values ('P06', 'Cuochi e fiamme', 'La7', 'Lux Vide');
insert into PROGRAMMATV (Codprogramma, Titolo, CanaleTV, Editore) values ('P07', 'Top Chef', 'DMAX', 'NBC Universal Global Networks Italia');
insert into PROGRAMMATV (Codprogramma, Titolo, CanaleTV, Editore) values ('P08', 'Samurai Gourmet', 'MTV', 'Wildside');
insert into PROGRAMMATV (Codprogramma, Titolo, CanaleTV, Editore) values ('P09', 'Hells Kitchen', 'Italia 1', 'Filmmaster Group');
insert into PROGRAMMATV (Codprogramma, Titolo, CanaleTV, Editore) values ('P10', 'Cucina Esplosiva', 'Canale 5', 'Taodue');

insert into APPARIZIONE (CodiceFiscaleChef, CodProgramma, NumeroPuntata, Data, OraInizio, OraFine) values ('C01','P01', 3 , '2003-12-16', '21:00', '21:45');
insert into APPARIZIONE (CodiceFiscaleChef, CodProgramma, NumeroPuntata, Data, OraInizio, OraFine) values ('C03','P10', 3 , '2017-06-20', '21:00', '21:45');
insert into APPARIZIONE (CodiceFiscaleChef, CodProgramma, NumeroPuntata, Data, OraInizio, OraFine) values ('C03','P08', 5 , '2017-09-25', '21:00', '21:45');
insert into APPARIZIONE (CodiceFiscaleChef, CodProgramma, NumeroPuntata, Data, OraInizio, OraFine) values ('C04','P02', 7 , '1998-10-07', '21:00', '21:45');
insert into APPARIZIONE (CodiceFiscaleChef, CodProgramma, NumeroPuntata, Data, OraInizio, OraFine) values ('C03','P04', 3 , '2014-11-05', '21:00', '21:45');
insert into APPARIZIONE (CodiceFiscaleChef, CodProgramma, NumeroPuntata, Data, OraInizio, OraFine) values ('C06','P05', 3 , '2010-07-16', '21:00', '21:45');
insert into APPARIZIONE (CodiceFiscaleChef, CodProgramma, NumeroPuntata, Data, OraInizio, OraFine) values ('C07','P06', 5 , '2010-12-17', '21:00', '21:45');
insert into APPARIZIONE (CodiceFiscaleChef, CodProgramma, NumeroPuntata, Data, OraInizio, OraFine) values ('C08','P07', 9 , '2010-02-14', '21:00', '21:45');
insert into APPARIZIONE (CodiceFiscaleChef, CodProgramma, NumeroPuntata, Data, OraInizio, OraFine) values ('C03','P02', 3 , '1997-05-26', '21:00', '21:45');
insert into APPARIZIONE (CodiceFiscaleChef, CodProgramma, NumeroPuntata, Data, OraInizio, OraFine) values ('C10','P03', 1 , '2005-12-28', '21:00', '21:45');

