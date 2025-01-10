import mqtt from 'mqtt';

const protocol = 'mqtt';
const host = '70ae867d15a74e699cbf5e0c0306eda4.s1.eu.hivemq.cloud';
const port = '8883';
// const clientId = `mqtt_${Math.random().toString(16).slice(3)}`;

const connectUrl = `${protocol}://${host}:${port}`;

export default function connectMQTT() {
	const client = mqtt.connect(connectUrl, {
		// clientId,
		clean: true,
		connectTimeout: 4000,
		username: 'Admin',
		password: 'Adminpassword1',
		reconnectPeriod: 1000,
	});
	client.on('connect', () => {
		console.log('Connected');
	});
}

connectMQTT();
