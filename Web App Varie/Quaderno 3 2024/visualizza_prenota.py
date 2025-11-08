from connect import *
import streamlit as st
import pandas as pd
import pymysql
from datetime import date


# Funzione per caricare i libri dal database
def carica_libri():
    db = connect_to_db()
    query = "SELECT ISBN, Titolo, Autore, Editore, Genere FROM LIBRI"
    libri = pd.read_sql(query, db)
    db.close()
    return libri

# Funzione per verificare se il membro esiste
def verifica_membro(cod_fisc):
    db = connect_to_db()
    query = "SELECT * FROM MEMBRI WHERE CodFisc = %s"
    result = pd.read_sql(query, db, params=(cod_fisc,))
    db.close()
    return not result.empty

# Funzione per prenotare un libro
def prenota_libro(isbn, cod_fisc, data_restituzione):
    db = connect_to_db()
    try:
        with db.cursor() as cursor:
            query = """
            INSERT INTO PRESTITI (ISBN, DataPrestito, CodFisc, DataRestituzione)
            VALUES (%s, CURDATE(), %s, %s)
            """
            cursor.execute(query, (isbn, cod_fisc, data_restituzione))
            db.commit()
        st.success("Prenotazione avvenuta con successo!")
    except Exception as e:
        st.error(f"Errore durante la prenotazione: {e}")
    finally:
        db.close()
        
def visualizza_prenota():

    # Titolo della pagina
    st.title("Visualizzazione e Prenotazione Libri")

    # Carica i libri dal database
    libri = carica_libri()

    # Widget per il filtro dei libri
    st.sidebar.header("Filtri per libri")

    # Filtro per genere
    generi = libri['Genere'].unique()
    genere_selezionato = st.sidebar.selectbox("Seleziona un genere", ["Tutti"] + list(generi))

    # Filtro per autore
    autori = libri['Autore'].unique()
    autore_selezionato = st.sidebar.selectbox("Seleziona un autore", ["Tutti"] + list(autori))

    # Filtro per editore
    editori = libri['Editore'].unique()
    editore_selezionato = st.sidebar.selectbox("Seleziona un editore", ["Tutti"] + list(editori))

    # Filtro per titolo
    titolo_selezionato = st.sidebar.text_input("Filtra per titolo", "")

    # Filtrare i libri in base alle scelte
    libri_filtrati = libri
    if genere_selezionato != "Tutti":
        libri_filtrati = libri_filtrati[libri_filtrati['Genere'] == genere_selezionato]
    if autore_selezionato != "Tutti":
        libri_filtrati = libri_filtrati[libri_filtrati['Autore'] == autore_selezionato]
    if editore_selezionato != "Tutti":
        libri_filtrati = libri_filtrati[libri_filtrati['Editore'] == editore_selezionato]
    if titolo_selezionato:
        libri_filtrati = libri_filtrati[libri_filtrati['Titolo'].str.contains(titolo_selezionato, case=False)]

    # Visualizza i libri filtrati
    st.write(f"Libri disponibili: {len(libri_filtrati)}")
    st.dataframe(libri_filtrati)

    # Selezione del libro da prenotare
    isbn_selezionato = st.selectbox("Seleziona un libro per la prenotazione", libri_filtrati['Titolo'])

    # Codice fiscale e data di restituzione
    cod_fisc = st.text_input("Inserisci il tuo Codice Fiscale")
    data_restituzione = st.date_input("Seleziona la data di restituzione", min_value=date.today())

    # Prenotazione del libro
    if st.button("Prenota libro"):
        if verifica_membro(cod_fisc):
            libro_isbn = libri_filtrati[libri_filtrati['Titolo'] == isbn_selezionato]['ISBN'].values[0]
            prenota_libro(libro_isbn, cod_fisc, data_restituzione)
        else:
            st.error("Codice Fiscale non valido. Per favore registrati come membro.")
