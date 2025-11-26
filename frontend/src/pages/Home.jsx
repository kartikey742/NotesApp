import React from 'react';

import '../css/Home.css';
import { useNavigate } from 'react-router-dom';
export function Home() {
  const navigate = useNavigate();
  const user = JSON.parse(localStorage.getItem('user'));
  return (
    <div className="landing-page">
      
      {/* 1. Navigation Bar */}
      <header className="navbar">
        <h1 className="logo">QuickNotes</h1>
       {!user && <div className="auth-buttons">
            <button className="btn btn-primary" onClick={()=>navigate("/signup")}>Sign Up</button>
            <button className="btn btn-primary" onClick={()=>navigate('/login')}>Log In</button>
        </div>}
      </header>

      {/* 2. Main "Hero" Section */}
      <main className="hero">
        <h2>Capture Your Ideas</h2>
        <p>The simple, fast, and beautiful notes app.</p>
        <button className="btn btn-primary btn-large" onClick={() => navigate('/login')}>
          Get Started for Free
        </button>
      </main>

      {/* 3. Footer */}
      <footer className="footer">
        <p>&copy; 2025 QuickNotes.</p>
      </footer>
      
    </div>
  );
}
