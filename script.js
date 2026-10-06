// ===== EDIT HERE =====
const GITHUB_URL = "https://github.com/rishilsriram/voice-controlled-wheelchair";
// =====================
document.documentElement.classList.add("js");
document.querySelectorAll("[data-github]").forEach(a => a.href = GITHUB_URL);

// mobile nav
const toggle = document.querySelector(".nav-toggle"), menu = document.getElementById("menu");
const setMenu = open => { toggle.setAttribute("aria-expanded", open); menu.classList.toggle("open", open); };
toggle.addEventListener("click", () => setMenu(toggle.getAttribute("aria-expanded") !== "true"));
menu.addEventListener("click", e => { if (e.target.closest("a")) setMenu(false); });
document.addEventListener("keydown", e => { if (e.key === "Escape") setMenu(false); });

// active section highlight
const links = [...menu.querySelectorAll('a[href^="#"]')];
const spy = new IntersectionObserver(es => es.forEach(e => {
  if (e.isIntersecting) links.forEach(l => l.classList.toggle("active", l.getAttribute("href") === "#" + e.target.id));
}), { rootMargin: "-45% 0px -50% 0px" });
links.forEach(l => { const s = document.querySelector(l.getAttribute("href")); if (s) spy.observe(s); });
// the "logic" section belongs to How It Works in the nav
const logic = document.getElementById("logic");
if (logic) new IntersectionObserver(es => es.forEach(e => e.isIntersecting && links.forEach(l => l.classList.toggle("active", l.getAttribute("href") === "#how"))), { rootMargin: "-45% 0px -50% 0px" }).observe(logic);

// back to top
const toTop = document.querySelector(".totop");
addEventListener("scroll", () => { toTop.hidden = scrollY < 700; }, { passive: true });

// scroll reveal (a few key blocks only)
const rv = document.querySelectorAll(".pipe, .metrics, .tbl, .road, .hw figure");
rv.forEach(el => el.classList.add("rv"));
const io = new IntersectionObserver(es => es.forEach(e => { if (e.isIntersecting) { e.target.classList.add("in"); io.unobserve(e.target); } }), { threshold: .12 });
rv.forEach(el => io.observe(el));
