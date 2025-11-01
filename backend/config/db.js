
const mongoose = require('mongoose');


const connectDB = async () => {
  const mongoURI = process.env.MONGO_URI ;
  try {
    // mongoose.connect returns a promise
    await mongoose.connect(mongoURI, {
      // These options are safe to include; newer mongoose ignores deprecated options.
      useNewUrlParser: true,
      useUnifiedTopology: true,
    });
    console.log(' MongoDB connected');
    return mongoose.connection;
  } catch (err) {
    console.error('❌ MongoDB connection error:', err.message || err);

  }
};

module.exports = connectDB;
