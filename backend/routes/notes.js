const express = require('express');
const router = express.Router();
const { addNote } = require('../controllers/Notes');
// router.get('/get-notes/:userId', getNotes);
router.post('/add-note/:userId', addNote);
// router.delete('/delete-note/:noteId', deleteNote);
// router.put('/update-note/:noteId', updateNote);
module.exports = router;