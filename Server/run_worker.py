import celeryinit
from server import app

if __name__ == "__main__":
	celeryinit.run_worker(app)