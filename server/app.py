from flask import Flask, request
import kociemba

app = Flask(__name__)
@app.route('/')
def home():
    return "server active"

@app.route('/solve')
def solve():
    scramble = request.args.get('state')
    return kociemba.solve(scramble)


state="DUFFUDUDDRRRRRLLLLFFBRFBLLBFFDDDURRUFULDLFBLDUBRBBBBUU"
if __name__ == "__main__":
    app.run()
