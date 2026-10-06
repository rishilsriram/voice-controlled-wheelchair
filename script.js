// ===== EDIT HERE =====
const GITHUB_URL = "https://github.com/rishilsriram/voice-controlled-wheelchair";
const GALLERY = [
  { src: "./assets/images/gallery-1.svg", alt: "Complete prototype", caption: "Complete prototype" },
  { src: "./assets/images/gallery-2.svg", alt: "Electronics assembly", caption: "Electronics assembly" },
  { src: "./assets/images/gallery-3.svg", alt: "Arduino setup", caption: "Arduino setup" },
  { src: "./assets/images/gallery-4.svg", alt: "Bluetooth module", caption: "Bluetooth module" },
  { src: "./assets/images/gallery-5.svg", alt: "Motor driver", caption: "Motor driver" },
  { src: "./assets/images/gallery-6.svg", alt: "Wiring", caption: "Wiring" },
  { src: "./assets/images/gallery-7.svg", alt: "Testing", caption: "Testing" },
  { src: "./assets/images/gallery-8.svg", alt: "Final prototype", caption: "Final prototype" }
];
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

// gallery + lightbox
const grid = document.getElementById("gallery-grid"), lb = document.getElementById("lightbox");
const lbImg = lb.querySelector("img"), lbCap = lb.querySelector("figcaption");
let cur = 0;
GALLERY.forEach((g, i) => {
  const li = document.createElement("li");
  li.innerHTML = `<button type="button" aria-label="Open image: ${g.caption}"><div class="im"><img src="${g.src}" alt="${g.alt}" loading="lazy" width="800" height="600"></div><span>${g.caption}</span></button>`;
  li.firstChild.addEventListener("click", () => show(i, true));
  grid.appendChild(li);
});
function show(i, open) {
  cur = (i + GALLERY.length) % GALLERY.length;
  lbImg.src = GALLERY[cur].src; lbImg.alt = GALLERY[cur].alt; lbCap.textContent = GALLERY[cur].caption;
  if (open && !lb.open) lb.showModal();
}
lb.querySelector(".lb-x").onclick = () => lb.close();
lb.querySelector(".lb-p").onclick = () => show(cur - 1);
lb.querySelector(".lb-n").onclick = () => show(cur + 1);
lb.addEventListener("click", e => { if (e.target === lb) lb.close(); });
lb.addEventListener("keydown", e => { if (e.key === "ArrowLeft") show(cur - 1); if (e.key === "ArrowRight") show(cur + 1); });

// back to top
const toTop = document.querySelector(".totop");
addEventListener("scroll", () => { toTop.hidden = scrollY < 700; }, { passive: true });

// scroll reveal (a few key blocks only)
const rv = document.querySelectorAll(".pipe, .metrics, .tbl, .road, .gallery, .hw figure");
rv.forEach(el => el.classList.add("rv"));
const io = new IntersectionObserver(es => es.forEach(e => { if (e.isIntersecting) { e.target.classList.add("in"); io.unobserve(e.target); } }), { threshold: .12 });
rv.forEach(el => io.observe(el));
