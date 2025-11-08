SET storage_engine=InnoDB;
CREATE DATABASE IF NOT EXISTS QUADERNO4;
SET FOREIGN_KEY_CHECKS=1;

USE QUADERNO4;  

DROP TABLE IF EXISTS VALUTAZIONE;
DROP TABLE IF EXISTS UTENTE;
DROP TABLE IF EXISTS CONTENUTO_MULTIMEDIALE;

CREATE TABLE UTENTE(
    CodFisc CHAR(20),
    Nome CHAR(50) NOT NULL,
    Cognome CHAR(50) NOT NULL,
    AnnoDiNascita INTEGER NOT NULL,
    PRIMARY KEY (CodFisc)
);

CREATE TABLE CONTENUTO_MULTIMEDIALE(
    CodContenuto INTEGER NOT NULL AUTO_INCREMENT,
    Genere CHAR(50) NOT NULL,
    Durata SMALLINT NOT NULL, 
    Titolo CHAR(50) NOT NULL,
    Descrizione CHAR(50),
    PRIMARY KEY (CodContenuto)
    );

ALTER TABLE CONTENUTO_MULTIMEDIALE AUTO_INCREMENT=0;

CREATE TABLE VALUTAZIONE(
    CodFisc CHAR(20),
    CodContenuto INTEGER NOT NULL,
    Data DATE NOT NULL,
    Valutazione INTEGER CHECK (Valutazione BETWEEN 1 AND 10),
    PRIMARY KEY (CodFisc,CodContenuto,Data),
    FOREIGN KEY (CodFisc)
        REFERENCES UTENTE (CodFisc)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (CodContenuto)
        REFERENCES CONTENUTO_MULTIMEDIALE (CodContenuto)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

insert into UTENTE (CodFisc, Nome, Cognome, AnnoDiNascita) values ('C01', 'Boone', 'Badrick', 1997);
insert into UTENTE (CodFisc, Nome, Cognome, AnnoDiNascita) values ('C02', 'Harmonia', 'Allmark', 2002);
insert into UTENTE (CodFisc, Nome, Cognome, AnnoDiNascita) values ('C03', 'Elden', 'Musgrove', 1999);
insert into UTENTE (CodFisc, Nome, Cognome, AnnoDiNascita) values ('C04', 'Catarina', 'Forri', 1997);
insert into UTENTE (CodFisc, Nome, Cognome, AnnoDiNascita) values ('C05', 'Cassandre', 'Whellans', 1996);
insert into UTENTE (CodFisc, Nome, Cognome, AnnoDiNascita) values ('C06', 'Enoch', 'Denzey', 2000);
insert into UTENTE (CodFisc, Nome, Cognome, AnnoDiNascita) values ('C07', 'Carmel', 'Canwell', 2000);
insert into UTENTE (CodFisc, Nome, Cognome, AnnoDiNascita) values ('C08', 'Bradley', 'Prattin', 1999);
insert into UTENTE (CodFisc, Nome, Cognome, AnnoDiNascita) values ('C09', 'Willyt', 'Legendre', 1998);
insert into UTENTE (CodFisc, Nome, Cognome, AnnoDiNascita) values ('C10', 'Friederike', 'Kearton', 1998);

insert into CONTENUTO_MULTIMEDIALE (Genere, Durata, Titolo) values ('Documentary', 66, 'Beijing Taxi');
insert into CONTENUTO_MULTIMEDIALE (Genere, Durata, Titolo) values ('Comedy', 35, 'Out of Towners, The');
insert into CONTENUTO_MULTIMEDIALE (Genere, Durata, Titolo) values ('Children|Romance', 77, 'Season for Miracles, A');
insert into CONTENUTO_MULTIMEDIALE (Genere, Durata, Titolo) values ('Drama|Film-Noir', 95, 'Desperate');
insert into CONTENUTO_MULTIMEDIALE (Genere, Durata, Titolo) values ('Adventure|Comedy|Crime|Romance', 50, 'Those Daring Young Men in Their Jaunty Jalopies');
insert into CONTENUTO_MULTIMEDIALE (Genere, Durata, Titolo) values ('Crime', 4, 'Any Number Can Win (Mélodie en sous-sol )');
insert into CONTENUTO_MULTIMEDIALE (Genere, Durata, Titolo) values ('Drama', 77, 'Anne of the Thousand Days');
insert into CONTENUTO_MULTIMEDIALE (Genere, Durata, Titolo) values ('Horror|Sci-Fi', 60, 'The Man Who Could Cheat Death');
insert into CONTENUTO_MULTIMEDIALE (Genere, Durata, Titolo) values ('Adventure|Comedy|Sci-Fi|Thriller', 88, 'Idiocracy');
insert into CONTENUTO_MULTIMEDIALE (Genere, Durata, Titolo) values ('Comedy|Drama', 42, 'How to Kill Your Neighbor''s Dog');

insert into VALUTAZIONE (CodFisc, CodContenuto, Data, Valutazione) values ('C01', 3 , '2003-12-16', 4);
insert into VALUTAZIONE (CodFisc, CodContenuto, Data, Valutazione) values ('C03', 3 , '2017-06-20', 5);
insert into VALUTAZIONE (CodFisc, CodContenuto, Data, Valutazione) values ('C03', 5 , '2017-09-25', 4);
insert into VALUTAZIONE (CodFisc, CodContenuto, Data, Valutazione) values ('C04', 7 , '1998-10-07', 5);
insert into VALUTAZIONE (CodFisc, CodContenuto, Data, Valutazione) values ('C03', 3 , '2014-11-05', 4);
insert into VALUTAZIONE (CodFisc, CodContenuto, Data, Valutazione) values ('C06', 3 , '2010-07-16', 6);
insert into VALUTAZIONE (CodFisc, CodContenuto, Data, Valutazione) values ('C07', 5 , '2010-12-17', 10);
insert into VALUTAZIONE (CodFisc, CodContenuto, Data, Valutazione) values ('C08', 9 , '2010-02-14', 4);
insert into VALUTAZIONE (CodFisc, CodContenuto, Data, Valutazione) values ('C03', 3 , '1997-05-26', 7);
insert into VALUTAZIONE (CodFisc, CodContenuto, Data, Valutazione) values ('C10', 1 , '2005-12-28', 1);

