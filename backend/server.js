// Import express
const express = require('express');
const cors = require('cors');
const connectDB = require('./config/db');
require('dotenv').config();
const userRoutes = require('./routes/auth');
const noteRoutes = require('./routes/notes');
const app = express();

// Define a port
const PORT = process.env.PORT || 4000;

// Middleware to parse JSON
app.use(express.json());

// ✅ Enable CORS
app.use(
  cors({
    origin: process.env.CLIENT_URL, // React app URL
    methods: ['GET', 'POST', 'PUT', 'DELETE'],
    credentials: true, // allow cookies, auth headers, etc.
  })
);

// Simple test route
app.get('/', (req, res) => {
  res.send('Hello, World!');
});
app.use('/api/auth', userRoutes);
app.use('/api/notes', noteRoutes);
(async () => {
  try {
    await connectDB();
    app.listen(PORT, () => {
      console.log(` Server running at http://localhost:${PORT}`);
    });
  } catch (err) {
    console.error(' Failed to start server due to DB connection issue', err);
    process.exit(1);
  }
})();
