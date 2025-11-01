import React, { useState } from 'react';
import '../css/Modal.css';
import { toast } from 'react-toastify';
export const Modal = ({ open, setOpen }) => {
  const [title, setTitle] = useState('');
  const [content, setContent] = useState('');

  const handleSubmit = async (e) => {
    e.preventDefault();
    if (!title.trim() || !content.trim()) return toast.error('Please fill out both fields.');
    const user = JSON.parse(localStorage.getItem('user'));
    const userId = user ? user._id : null;
    if (!userId) return toast.error('User not found. Please log in again.');
    const newNote = {
      
      title,
      content,
      lastModified: new Date().toISOString(),
    };

  const res=await fetch(`${process.env.React_APP_API_URL}/notes/add-note/${userId}`,{
    method:'POST',
    headers:{'Content-Type':'application/json'},
    body:JSON.stringify(newNote)
  });
  const data=await res.json();
  console.log(data);

    setTitle('');
    setContent('');
  };

  return (
    <form className="add-note-form" onSubmit={handleSubmit}>
      <input
        type="text"
        className="note-title-input"
        placeholder="Enter title..."
        value={title}
        onChange={(e) => setTitle(e.target.value)}
      />
      <textarea
        className="note-content-input"
        placeholder="Write your note..."
        rows="6"
        value={content}
        onChange={(e) => setContent(e.target.value)}
      ></textarea>
      <button type="submit" className="save-btn">Save Note</button>
      <button type="button" className="cnc-btn" onClick={() => setOpen(false)}>Cancel</button>
    </form>
  );
};
