import React, { useState } from "react";
import { Navigate } from "react-router-dom";
import { toast } from "react-toastify";
import { useNavigate } from "react-router-dom";
const LoginPage = () => {
  const navigate = useNavigate();
  const [formData, setFormData] = useState({
    email: "",
    password: "",
  });

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData((prev) => ({
      ...prev,
      [name]: value,
    }));
  };

  const handleSubmit = async (e) => {
    e.preventDefault();

    try {
      const response = await fetch(`${process.env.React_APP_API_URL}auth/login`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(formData),
      });

      const result = await response.json();
      console.log(result);
      localStorage.setItem('user', JSON.stringify(result.user));
      if (response.ok) {
        toast.success("Login successful!");
        setFormData({ email: "", password: "" });
        navigate('/dashboard');
        
      } else {
        toast.error(result.message || "Invalid credentials");
      }
    } catch (error) {
      console.error(error);
      toast.error("Failed to connect to server");
    }
  };

  return (
    <div className="login-page">
      <div className="login-container">
        {/* Left Side - Image */}
        <div className="login-image-section">
          <img
            src="https://placehold.co/800x1000/818cf8/ffffff?text=Capture+Your+Ideas"
            alt="Workspace background"
            onError={(e) => {
              e.currentTarget.onerror = null;
              e.currentTarget.src =
                "https://placehold.co/800x1000/cccccc/ffffff?text=Image+Not+Found";
            }}
          />
          <div className="image-overlay">
            <h1>All your thoughts, perfectly organized.</h1>
            <p>Log in to access your digital notebook.</p>
          </div>
        </div>

        {/* Right Side - Form */}
        <div className="login-form-section">
          <div className="logo">
            <svg
              xmlns="http://www.w3.org/2000/svg"
              className="logo-icon"
              viewBox="0 0 24 24"
              fill="none"
              stroke="currentColor"
              strokeWidth="2"
              strokeLinecap="round"
              strokeLinejoin="round"
            >
              <path d="M15.232 5.232l3.536 3.536m-2.036-5.036a2.5 2.5 0 113.536 3.536L6.5 21.036H3v-3.572L16.732 3.732z"></path>
            </svg>
            <h2>NotesApp</h2>
          </div>

          <h3 className="welcome-text">Welcome Back!</h3>
          <p className="subtext">Please enter your details to sign in.</p>

          <form className="login-form" onSubmit={handleSubmit}>
            <label htmlFor="email">Email Address</label>
            <input
              type="email"
              id="email"
              name="email"
              value={formData.email}
              onChange={handleChange}
              placeholder="Enter your email"
              required
            />

            <div className="password-row">
              <label htmlFor="password">Password</label>
              <a href="#" className="forgot-link">
                Forgot password?
              </a>
            </div>
            <input
              type="password"
              id="password"
              name="password"
              value={formData.password}
              onChange={handleChange}
              placeholder="Enter your password"
              required
            />

            <button type="submit" className="btn-gradient">
              Sign In
            </button>
          </form>

          <div className="divider">
            <span>Or continue with</span>
          </div>

          <div className="social-buttons">
            <button className="social-btn">
              <img
                src="https://www.svgrepo.com/show/475656/google-color.svg"
                alt="Google"
              />
              Google
            </button>
          </div>

          <p className="signup-text">
            Don't have an account?{" "}
            <a href="signin" className="signup-link">
              Sign up now
            </a>
          </p>
        </div>
      </div>
    </div>
  );
};

export default LoginPage;
