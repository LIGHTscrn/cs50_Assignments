from flask import Flask, redirect, render_template, session, request
from flask_session import Session

app = Flask(__name__)

app.config["SESSION_PERMANANT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

@app.route("/")
def index():
    return render_template("index.html" , name=session.get("name"))

@app.route("/login", methods=["GET","POST"])
def login():
    if request.method == "POST":
        session["name"] = request.form.get("Name")
        return redirect("/")
    return render_template("login.html")

@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")