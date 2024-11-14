import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])

def index():

    if request.method == "POST":

        # TODO: Add the user's entry into the database
        if not request.form.get("Name") or not request.form.get("Month") or not request.form.get("Day"):

            return render_template("index.html", place_holder1="Enter all fields!")

        elif int(request.form.get("Day")) > 31 or int(request.form.get("Month")) > 12:

            return render_template("index.html", place_holder1="Invalid day or month")

        elif int(request.form.get("Day")) > 28 or int(request.form.get("Month")) == 2:

            return render_template("index.html", place_holder1="Invalid day or month")

        else:

            name = request.form.get("Name")

            month = request.form.get("Month")

            day = request.form.get("Day")

            db.execute("INSERT INTO birthdays (name,month,day) VALUES(? ,? ,?)", name, month, day)


        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        rows = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays = rows)


