from flask import Flask
from flask_sqlalchemy import SQLAlchemy
import json
from flask import request

app = Flask(__name__)
app.config.from_pyfile('app_settings.cfg')
db = SQLAlchemy(app)

from models import *

@app.after_request
def after_request(response):
	try: 
		db.session.commit()
	except:
		db.session.rollback()
	finally:
		db.session.close()

	return response

@app.route('/lobbies')
def getLobbies():
	lobbies = { "lobbies": []}
	lobbies["lobbies"] = Lobby.query.filter(Lobby.num_players != Lobby.max_players).all()
	lobbies["lobbies"] = [ l.to_json() for l in lobbies["lobbies"] ]
	return json.dumps(lobbies)

@app.route('/lobbies/new/<int:max_players>')
def newLobby(max_players):
	assert(max_players > 0)
	# get or create client
	client = get_or_create(db.session, Client, ip_address=request.remote_addr)

	#create lobby
	l = Lobby(max_players, num_players=1)
	l.host = client #set authoritive host of lobby
	db.session.add(l) # add to db
	db.session.flush() # allow ids to validate
	client.lobby_id = l.id # link client to lobby
	db.session.commit() # commit everything

	return str(client.lobby_id)

@app.route('/lobbies/join/<int:lobby_id>')
def joinLobby(lobby_id):
	lobby = Lobby.query.get(lobby_id)
	assert(lobby)

	# get or create client
	client = get_or_create(db.session, Client, ip_address=request.remote_addr)
	client.lobby_id = lobby_id
	
	db.session.commit()
	return str(client.lobby_id)

@app.route('/lobbies/leave/<int:lobby_id>')
def leaveLobby(lobby_id):
	lobby = Lobby.query.get(lobby_id)
	assert(lobby)

	# get or create client
	client = get_or_create(db.session, Client, ip_address=request.remote_addr)
	client.lobby_id = lobby_id
	
	db.session.commit()
	return str(client.lobby_id)


if __name__ == "__main__":
    app.run()