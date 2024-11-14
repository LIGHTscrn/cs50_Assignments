import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    total_price = 0
    processed_price = []
    user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    cash = user[0]["cash"]
    print("OOOPP:::", cash)
    username = user[0]["username"]
    # history = db.execute("SELECT * FROM history WHERE username = ?", username)
    shares = db.execute(
        "SELECT shares,SUM(number) FROM history WHERE username = ? GROUP BY shares ORDER BY shares ASC",
        username,
    )

    for share in shares:
        symbol = lookup(share["shares"])
        share_name = symbol["symbol"]
        share_price = symbol["price"]
        count = share["SUM(number)"]
        final_price = int(count) * int(share_price)
        processed_price.append(
            {
                "price": share_price,
                "symbol": share_name,
                "number": count,
                "total": final_price,
            }
        )
    for i in processed_price:
        total_price = total_price + i["total"]
    final = cash + total_price
    return render_template(
        "index.html", processed_price=processed_price, cash=cash, final=final
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("Input field should not be left blank")
        else:
            stock = lookup(symbol)
            if not stock:
                return apology("invalid")
        if not shares:
            return apology("Enter a valid number")

        try:
            number = int(shares)
            if number <= 0 or not number.is_integer():
                return apology("choose a greater amount")
        except ValueError:
            return apology("invalid number of shares")
        amount = number * int(stock["price"])
        current_amount = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        updated_amount = int(current_amount[0]["cash"]) - amount
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", updated_amount, session["user_id"]
        )
        username = db.execute(
            "SELECT username FROM users WHERE id = ?", session["user_id"]
        )
        db.execute(
            "INSERT INTO history (id ,username, shares , number) VALUES (? ,?, ? , ?)",
            session["user_id"],
            username[0]["username"],
            stock["symbol"],
            number,
        )
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    money = []
    username = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    history = db.execute(
        "SELECT * FROM history WHERE username = ?", username[0]["username"]
    )
    for hist in history:
        data = lookup(hist["shares"])
        symbol = data["symbol"]
        price = float(data["price"])
        number = float(hist["number"])
        amount = float(number * price)
        username = hist["username"]

        money.append(
            {"username": username, "symbol": symbol, "number": number, "amount": amount}
        )

    return render_template("history.html", money=money)


@app.route("/login", methods=["GET", "POST"])
def login():
    session.clear()

    if request.method == "POST":

        if not request.form.get("username"):
            return apology("must provide username", 403)

        elif not request.form.get("password"):
            return apology("must provide password", 403)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():

    session.clear()

    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    x = None
    y = None
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol and symbol.isalpha():
            stock = lookup(symbol)
            if stock:
                x = stock["symbol"]
                y = stock["price"]
            else:
                return apology("Invalid input")
        else:
            return apology("No input detected")
    return render_template("quotes.html", x=x, y=y)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        username = request.form.get("username")
        if not username:
            return apology("NO valid username")
        password = request.form.get("password")
        if not password:
            return apology("NO valid password")
        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("password didnt match")
        if password != confirmation:
            return apology("password didnt match")
        passkey = generate_password_hash(password)

        count = db.execute(
            "SELECT COUNT(username) FROM users WHERE username = ?", username
        )
        if int(count[0]["COUNT(username)"]) == 0:
            db.execute(
                "INSERT INTO users (username,hash) VALUES(? ,? )", username, passkey
            )
            return redirect("/login")
        else:
            return apology("username already taken")
    else:
        return render_template("registration.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    to_sell = []

    something = db.execute(
        "SELECT DISTINCT shares FROM history WHERE id = ?", session["user_id"]
    )
    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    user_name = username[0]["username"]
    for some in something:

        shares = some["shares"]

        share_num = db.execute(
            "SELECT SUM(number) AS total FROM history WHERE id = ? AND shares = ?",
            session["user_id"],
            shares,
        )

        if share_num:
            to_sell.append({"shares": shares, "num": share_num[0]["total"]})

    if request.method == "POST":

        number = int(request.form.get("shares"))
        if not number or number < 0:
            return apology("pick a number greater than 0")

        symbol = request.form.get("symbol")
        if not symbol:
            return apology("invalid share")

        upperlimit = db.execute(
            "SELECT SUM(number) AS total FROM history WHERE shares = ? AND id = ?",
            symbol,
            session["user_id"],
        )
        if number > upperlimit[0]["total"]:
            return apology("Ran out of shares to sell")

        share = lookup(symbol)
        print(share, "which one is this one")
        price = int(share["price"])
        total = number * price
        current_price = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        final_price = current_price[0]["cash"] + total
        new_number = 0 - number
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", final_price, session["user_id"]
        )
        db.execute(
            "INSERT INTO history (username , id , shares , number) VALUES (? ,? ,? ,?)",
            user_name,
            session["user_id"],
            symbol,
            new_number,
        )
        return redirect("/")
    else:
        return render_template("sell.html", to_sell=to_sell)


@app.route("/add_cash", methods=["GET", "POST"])
def add_cash():
    if request.method == "POST":
        amount = request.form.get("amount")
        if not amount:
            return apology("Enter a valid amount")
        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?", amount, session["user_id"]
        )
        return redirect("/")
    else:
        return render_template("add_cash.html")
