import type { Config } from 'tailwindcss';
import { PluginAPI } from 'tailwindcss/types/config';

const config: Config = {
  content: [
    "./pages/**/*.{js,ts,jsx,tsx,mdx}",
    "./components/**/*.{js,ts,jsx,tsx,mdx}",
    "./app/**/*.{js,ts,jsx,tsx,mdx}",
  ],
  theme: {
    extend: {
      fontSize: {
        "10xl": "10rem",
        "11xl": "11rem",
        "12xl": "12rem",
        "13xl": "13rem",
      },
      fontFamily: {
        sans: ['Inter', 'Helvetica', 'Arial', 'sans-serif'], // Replace 'Inter' with your desired font
      },
      colors: {
        background: "var(--background)",
        foreground: "var(--foreground)",
        navyBlue: '#05445e',
        blueGrotto: '#189ab4',
        blueGreen: '#75e6da',
        babyBlue: '#d4f1f4',
        primary: "#050816",
        secondary: "#aaa6c3",
        tertiary: "#151030",
        "black-100": "#100d25",
        "black-200": "#090325",
        "white-100": "#f3f3f3",
        'darker-blue': '#000a1f', 
        'darker-purple': '#1e1b4b',
        'darker-gray': '#0d0d0d', 
        boxShadow: {
          "image-shadow": "5px 5px 20px #2e2e2e",
          "back-cover-shadow": "-10px 0 50px 10px #2e2e2e",
        },
        gray: {
          200: "#D5DAE1"
        },
        black: {
          DEFAULT: "#000",
          500: "#1D2235"
        },
        blue: {
          500: "#2b77e7"
        }
      },
      animation: {
        blink: 'blink 1s step-end infinite',
        fadeInShort: 'fadeIn 1s ease-in-out',
        fadeIn: 'fadeIn 2s ease-in-out',
        fadeInLong: 'fadeIn 3s ease-in-out',
        shake: 'shake 0.5s ease-in-out',
        rotate: 'rotate 10s linear infinite',
        gradient: 'gradient 3s ease infinite',
        'gradient-move': 'gradient 3s ease infinite',
        slideInOut: 'slideInOut 1s ease-out forwards',
        hammer: 'hammer 0.5s ease-in-out infinite',
        "horizontal-scroll": "horizontal-scroll linear 16s infinite ",
        "horizontal-scroll-2": "horizontal-scroll-2 linear 16s infinite ",
      },
      keyframes: {
        blink: {
          '0%, 100%': { opacity: "1" },
          '50%': { opacity: "0" },
        },
        fadeIn: {
          '0%': { opacity: '0' },
          '100%': { opacity: '1' },
        },
        shake: {
          '0%': { transform: 'translateX(0)' },
          '25%': { transform: 'translateX(-10px)' },
          '50%': { transform: 'translateX(10px)' },
          '75%': { transform: 'translateX(-10px)' },
          '100%': { transform: 'translateX(0)' },
        },
        rotate: {
          '0%': { transform: 'rotateY(0deg)' },
          '100%': { transform: 'rotateY(360deg)' },
        },
        gradient: {
          '0%': { backgroundPosition: '0% 50%' },
          '50%': { backgroundPosition: '100% 50%' },
          '100%': { backgroundPosition: '0% 50%' },
        },
        float: {
          '0%': { backgroundPosition: '0% 50%' },
          '50%': { backgroundPosition: '100% 50%' },
          '100%': { backgroundPosition: '0% 50%' },
        },
        slideInOut: {
          '0%': {
            transform: 'translateX(100%)',
          },
          '20%': {
            transform: 'translateX(0)',
          },
          '80%': {
            transform: 'translateX(0)',
          },
          '100%': {
            transform: 'translateX(300%)',
          },
        },
        hammer: {
          '0%': { transform: 'rotate(0deg)' },
          '50%': { transform: 'rotate(-30deg)' },
          '100%': { transform: 'rotate(0deg)' },
        },
        "horizontal-scroll": {
          from: { transform: "translateX(0)" },
          to: { transform: "translateX(-100%)" },
        },
        "horizontal-scroll-2": {
          from: { transform: "translateX(100%)" },
          to: { transform: "translateX(0)" },
        },
      },
    },
  },
  plugins: [
    function ({ addUtilities }: PluginAPI) {
      addUtilities(
        {
          '.perspective-900': {
            perspective: '900px',
          },
          '.preserve-3d': {
            transformStyle: 'preserve-3d',
          },
          '.transition-transform-075s': {
            transition: 'transform 0.75s ease',
          },
          '.rotate-y-30': {
            transform: 'rotateY(-30deg)',
          },
          '.content-empty': {
            content: '" "',
          },
          '.page-transform': {
            transform: 'translateX(calc(200px - 50px / 2 - 3px)) rotateY(90deg) translateX(25px)',
          },
          '.back-cover-transform': {
            transform: 'translateZ(-50px)',
          },
        },
        // ['responsive', 'hover']
      );
    },
  ],
};



export default config;
