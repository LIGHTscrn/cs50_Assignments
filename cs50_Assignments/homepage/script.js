document.addEventListener("DOMContentLoaded", () =>{
    const hamburgerMenu = document.querySelector(".hamburger_menu");
    const menu = document.querySelector(".menu");

    hamburgerMenu.addEventListener('click', () => {
        menu.classList.toggle("active");
    });
});
