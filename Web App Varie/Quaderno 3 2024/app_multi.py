import streamlit as st

# Importiamo le funzioni definite sopra
from homepage import homepage
from visualizza_prenota import visualizza_prenota
from registra_membro import registra_membro

st.sidebar.title("Menu")
opzione = st.sidebar.radio(
    "Naviga:",
    ["Homepage", "Visualizza e Prenota", "Registra Membro"]
)

if opzione == "Homepage":
    homepage()
elif opzione == "Visualizza e Prenota":
    visualizza_prenota()
elif opzione == "Registra Membro":
    registra_membro()
