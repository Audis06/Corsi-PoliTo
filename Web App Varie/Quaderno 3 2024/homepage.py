import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt

import pymysql

from connect import *

def homepage():
    st.title("Gestione Biblioteca")
    st.markdown("### Benvenuto nella Biblioteca Online")
    
    st.markdown("""
                Questo è il sistema di gestione della **Biblioteca Online** che ti permette di esplorare i libri disponibili, 
                effettuare prenotazioni e visualizzare informazioni statistiche sui contenuti della biblioteca.
                """)

    db = connect_to_db()
    #query_libri = "SELECT Genere, COUNT(*) AS Totale FROM LIBRI GROUP BY Genere"
    query_disponibili = """
        SELECT Genere, COUNT(*) AS Disponibili
        FROM LIBRI
        WHERE ISBN NOT IN (SELECT ISBN FROM PRESTITI WHERE DataRestituzione >= CURDATE())
        GROUP BY Genere
    """
    query_status = """
        SELECT 'Disponibili' AS Stato, COUNT(*) AS Totale
        FROM LIBRI
        WHERE ISBN NOT IN (
            SELECT ISBN 
            FROM PRESTITI 
        )
        UNION ALL
        SELECT 'Prenotati' AS Stato, COUNT(*) AS Totale
        FROM LIBRI
        WHERE ISBN IN (
            SELECT ISBN 
            FROM PRESTITI 
        )
    """
    
    #libri_totali = pd.read_sql(query_libri, db)
    libri_disponibili = pd.read_sql(query_disponibili, db)
    libri_status = pd.read_sql(query_status,db)

    fig, ax = plt.subplots(1, 2, figsize=(25, 10))

    # Grafico a torta
    wedges, texts, autotexts = ax[0].pie(libri_status['Totale'], labels=libri_status['Stato'], autopct='%1.1f%%', startangle=140)
    # Ingrandire le etichette (i nomi dei libri disponibili e prenotati)
    for text in texts:
        text.set_fontsize(20)  # Ingrandisci le etichette

    # Ingrandire le percentuali
    for autotext in autotexts:
        autotext.set_fontsize(20)  # Ingrandisci le percentuali
    ax[0].set_title("Distribuzione Libri disponibili", fontsize=35,fontweight='bold')
    
    

    # Grafico a barre
    ax[1].bar(libri_disponibili['Genere'], libri_disponibili['Disponibili'], color='skyblue')
    ax[1].set_title("Libri Disponibili per Genere", fontsize=35,fontweight='bold')
    ax[1].set_ylabel("Numero di Libri", fontsize=20)
    ax[1].set_xticklabels(libri_disponibili['Genere'], rotation=45, fontsize=20)

    st.pyplot(fig)
    db.close()
