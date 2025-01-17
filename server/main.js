import express from 'express';

const app = express();
const PORT = 3000;

let competition = {
	running: false,
	startTime: 0,
};

app.post('/', (req, res) => {
	if (competition.running) {
		const receivedTime = new Date();
		console.log(`Button press after ${receivedTime - competition.startTime} ms`);
		res.send('win');

		endCompetition();
	} else {
		res.send('loss');
	}
});

function addMessage(message) {}

function runCompetition() {
	competition.running = true;
	competition.competitionStartTime = new Date();
}

function endCompetition() {
	competition.running = false;
}

app.listen(PORT, () => {
	console.log(`Server is running on host http://localhost:${PORT}`);
});

runCompetition();
