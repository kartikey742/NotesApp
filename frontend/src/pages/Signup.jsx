import React, { useState } from "react";
import  { toast } from "react-toastify";

const SignupPage = () => {
  const [formData, setFormData] = useState({
    firstName: "",
    lastName: "",
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
      const response = await fetch(`${process.env.React_APP_API_URL}/auth/signup`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(formData),
      });

      const result = await response.json();
      console.log(result);
      
      if (response.ok) {
        toast.success("Account created successfully!");
        setFormData({ firstName: "", lastName: "", email: "", password: "" });
        // Navigate to login or dashboard
      } else {
        
        
        toast.error(result.message || "Failed to create account");
      }
    } catch (error) {
      console.log(error);
      toast.error("Failed to connect to server");
    }
  };

  return (
    <div className="signup-page">
      <div className="signup-container">
        {/* Left Side - Image */}
        <div className="signup-image-section">
          <img
            src="https://placehold.co/800x1000/818cf8/ffffff?text=Start+Your+Journey"
            alt="Signup background"
            onError={(e) => {
              e.currentTarget.onerror = null;
              e.currentTarget.src =
                "https://placehold.co/800x1000/cccccc/ffffff?text=Image+Not+Found";
            }}
          />
          <div className="image-overlay">
            <h1>Capture ideas, organize life.</h1>
            <p>Create an account to start your journey.</p>
          </div>
        </div>

        {/* Right Side - Form */}
        <div className="signup-form-section">
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

          <h3 className="welcome-text">Create Account</h3>
          <p className="subtext">Please fill in your information below.</p>

          <form className="signup-form" onSubmit={handleSubmit}>
            <div className="name-row">
              <div className="form-group">
                <label htmlFor="firstName">First Name</label>
                <input
                  type="text"
                  id="firstName"
                  name="firstName"
                  value={formData.firstName}
                  onChange={handleChange}
                  placeholder="First name"
                  required
                />
              </div>
              <div className="form-group">
                <label htmlFor="lastName">Last Name</label>
                <input
                  type="text"
                  id="lastName"
                  name="lastName"
                  value={formData.lastName}
                  onChange={handleChange}
                  placeholder="Last name"
                  required
                />
              </div>
            </div>

            <div className="form-group">
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
            </div>

            <div className="form-group">
              <label htmlFor="password">Password</label>
              <input
                type="password"
                id="password"
                name="password"
                value={formData.password}
                onChange={handleChange}
                placeholder="Create a password"
                required
              />
            </div>

            <button type="submit" className="btn-gradient">
              Create Account
            </button>
          </form>

          <div className="divider">
            <span>Or sign up with</span>
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

          <p className="login-text">
            Already have an account?{" "}
            <a href="#" className="login-link">
              Log in
            </a>
          </p>
        </div>
      </div>
    </div>
  );
};

export default SignupPage;