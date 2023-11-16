/** @type {import('tailwindcss').Config} */
module.exports = {
  content: ["./src/**/*.{tsx, html}"],
  theme: {
    extend: {
        colors:{
            gura_main:"#337094",
            gura_gray: "#EDEDF6",
            main: "#C9E6FD"
        },
    }
  },
  plugins: [],
}

