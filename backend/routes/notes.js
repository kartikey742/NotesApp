const express = require('express');
const router = express.Router();
const { addNote,getNotes,updateNote,deleteNote} = require('../controllers/Notes');
const verifyToken = require('../middlewares/verifyToken');
router.get('/get-notes/:userId', verifyToken, getNotes);
router.post('/add-note/:userId', verifyToken, addNote);
router.delete('/delete-note/:noteId', verifyToken, deleteNote);
router.put('/update-note/:noteId', verifyToken, updateNote);
module.exports = router;