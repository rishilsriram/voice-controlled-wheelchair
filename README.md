# VOICECHAIR: Voice-Controlled Wheelchair Using Arduino

A static project website for an Arduino-based voice-controlled wheelchair prototype (Arduino UNO, HC-05 Bluetooth, L298N motor driver, DC motors, 12V supply). Educational prototype, not a certified medical mobility device.

## Technology stack
HTML5, CSS3 and vanilla JavaScript. No build step, no dependencies, no API keys. Fonts (Instrument Sans, JetBrains Mono) load from Google Fonts with system fallbacks.

## File structure
```
index.html        page content
style.css         all styling (colours are variables at the top)
script.js         GITHUB_URL, GALLERY list, navigation, lightbox
assets/images/    prototype, hardware and gallery images
assets/icons/     favicon
```

## Run locally
Open `index.html` in a browser, or from this folder run `python3 -m http.server 8000` and visit http://localhost:8000.

## Replace images
Copy your photos into `assets/images/` (JPG/WebP, about 1600x1200, 4:3 works best).
- Gallery: edit the `GALLERY` list at the top of `script.js` (`src`, `alt`, `caption`).
- Hero and hardware images: change the `src`/`alt` in `index.html` (`prototype.svg`, `arduino.svg`, `hc05.svg`, `l298n.svg`, `motors.svg`, `power.svg`).
- Social preview: update the `og:image` tag in `index.html`; for sharing it works best as an absolute URL to a .jpg/.png once deployed.

## Edit content
Text lives in `index.html`. The GitHub URL is the `GITHUB_URL` variable in `script.js`; it updates every GitHub link. Test results are in the table in the Testing section. Edit them to match your real tests.

## Deploy with GitHub Pages
1. Put these files at the root of the repository (or a `docs/` folder).
2. On GitHub: Settings, Pages, Source "Deploy from a branch", choose `main` and `/ (root)` (or `/docs`), then Save.
3. After a minute the site is live at `https://rishilsriram.github.io/voice-controlled-wheelchair/`.

All paths are relative (`./assets/...`), so it works under the `/voice-controlled-wheelchair/` sub-path.
