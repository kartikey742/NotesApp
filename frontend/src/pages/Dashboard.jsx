import React from 'react'
import '../css/dashboard.css'
import { IoAdd } from 'react-icons/io5';
import { useState } from 'react';
import {Modal} from '../modals/Modal';
export const Dashboard = () => {
    
const dummyNotesData = [
  {
    id: 1,
    title: 'Meeting Notes - Project Phoenix',
    content: 'Discussed Q4 roadmap. Key takeaways: focus on user retention, A/B test new onboarding flow. John to follow up with a detailed plan by EOD Friday.',
    lastModified: '2025-10-06T10:00:00Z',
  },
  {
    id: 2,
    title: 'Grocery List',
    content: 'Milk, Bread, Eggs, Cheese, Apples, Bananas, Chicken breast, Spinach.',
    lastModified: '2025-10-08T09:30:00Z',
  },
  {
    id: 3,
    title: 'Brainstorming - New App Idea',
    content: 'A social network for gardeners. Users can share pictures of their plants, ask for advice, and trade seeds. Possible name: "Gardenly". Monetization through premium features like advanced plant identification.',
    lastModified: '2025-10-07T15:45:00Z',
  },
  {
    id: 4,
    title: 'Book Recommendations',
    content: '1. "Project Hail Mary" by Andy Weir\n2. "The Midnight Library" by Matt Haig\n3. "Atomic Habits" by James Clear',
    lastModified: '2025-09-28T11:20:00Z',
  },
   {
    id: 1,
    title: 'Meeting Notes - Project Phoenix',
    content: 'Discussed Q4 roadmap. Key takeaways: focus on user retention, A/B test new onboarding flow. John to follow up with a detailed plan by EOD Friday.',
    lastModified: '2025-10-06T10:00:00Z',
  },
  {
    id: 2,
    title: 'Grocery List',
    content: 'Milk, Bread, Eggs, Cheese, Apples, Bananas, Chicken breast, Spinach.',
    lastModified: '2025-10-08T09:30:00Z',
  },
  {
    id: 3,
    title: 'Brainstorming - New App Idea',
    content: 'A social network for gardeners. Users can share pictures of their plants, ask for advice, and trade seeds. Possible name: "Gardenly". Monetization through premium features like advanced plant identification.',
    lastModified: '2025-10-07T15:45:00Z',
  },
  {
    id: 4,
    title: 'Book Recommendations',
    content: '1. "Project Hail Mary" by Andy Weir\n2. "The Midnight Library" by Matt Haig\n3. "Atomic Habits" by James Clear',
    lastModified: '2025-09-28T11:20:00Z',
  },
];

const [open, setOpen] = useState(false);

  return (
  <div className={`notes-container ${open ? "active" : ""}`}>

        {dummyNotesData.map((note) => (
          <div key={note.id} className="note-card">
            <h2 className="note-title">{note.title}</h2>
            <p className="note-content">{note.content}</p>
          </div>
        ))}
        <div>

        <button className='add' onClick={() => setOpen(true)}><IoAdd /></button>
        </div>
        {open && <div className="modal-overlay"><Modal open={open} setOpen={setOpen} /></div>}
      </div>
  )
}
