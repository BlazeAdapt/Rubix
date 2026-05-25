from flask import Flask, request
import kociemba

app = Flask(__name__)
@app.route('/')
def home():
    return "server active"

@app.route('/solve')
def solve():
    scramble=request.data.decode('utf-8')
    return kociemba.solve(scramble)


state="DUFFUDUDDRRRRRLLLLFFBRFBLLBFFDDDURRUFULDLFBLDUBRBBBBUU"
if __name__ == "__main__":
    app.run()
