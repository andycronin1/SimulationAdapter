# streamlit_app.py
import streamlit as st
import requests

st.title("Simulation Control")

command = st.selectbox("Choose a command", ["drive_forward", "create_box"])

if st.button("Send Command"):
    response = requests.post(
        "http://localhost:8080/control",
        json={"command": command}
    )
    st.write("Response from C++ backend:", response.json())