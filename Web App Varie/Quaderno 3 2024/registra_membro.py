from connect import *
import streamlit as st
import pymysql
import pandas as pd

# Funzione per verificare se il codice fiscale o l'email sono già presenti nel database
def verifica_membro(cod_fisc, email):
    db = connect_to_db()
    try:
        with db.cursor() as cursor:
            query = "SELECT * FROM MEMBRI WHERE CodFisc = %s OR Email = %s"
            cursor.execute(query, (cod_fisc, email))
            result = cursor.fetchall()
            if result:
                return True  # Membro già esistente
            return False  # Membro non esistente
    finally:
        db.close()

# Funzione per registrare un nuovo membro
def registra(cod_fisc, nome, cognome, data_nascita, email, telefono):
    db = connect_to_db()
    try:
        with db.cursor() as cursor:
            query = """
            INSERT INTO MEMBRI (CodFisc, Nome, Cognome, DataNascita, Email, Telefono) 
            VALUES (%s, %s, %s, %s, %s, %s)
            """
            cursor.execute(query, (cod_fisc, nome, cognome, data_nascita, email, telefono))
            db.commit()
            return True
    except Exception as e:
        return False  # Gestire eventuali errori durante l'inserimento
    finally:
        db.close()

def registra_membro():
    # Titolo della pagina
    st.title("Registrazione Nuovo Membro")

    # Modulo di registrazione
    cod_fisc = st.text_input("Codice Fiscale (16 caratteri)", max_chars=16)
    nome = st.text_input("Nome")
    cognome = st.text_input("Cognome")
    data_nascita = st.date_input("Data di Nascita")
    email = st.text_input("Email")
    telefono = st.text_input("Telefono (opzionale)", "")

    # Bottone per registrare
    if st.button("Registrati"):
        telefono = telefono if telefono else None
        # Verifica se il codice fiscale o l'email sono già presenti nel database
        if verifica_membro(cod_fisc, email):
            st.error("Errore: Il codice fiscale o l'email sono già registrati.")
        else:
            # Tentativo di registrazione del nuovo membro
            if registra(cod_fisc, nome, cognome, data_nascita, email, telefono):
                st.success("Registrazione avvenuta con successo!")
            else:
                st.error("Errore durante la registrazione. Riprova.")
