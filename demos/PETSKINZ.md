# Junie Ultimate — Build Basil Demo Site: PetSkinz (“Alive Again”)

## Goal
Create a single-page, tongue-in-cheek demo website that showcases:
1) Basil templating via `<?basil ... ?>` arrays + loops
2) A simple contact form that emails Erik for estimates
3) File upload handling (pet photo) as part of the form

This is a **satirical demo site**. Keep it comedic, glossy, and slightly unsettling — like a too-cheerful mall kiosk brand.

## Site Identity
- Name: **PetSkinz**
- Trademark-ish slogan: **“Alive Again”**
- Vibe: “cheerfully unethical luxury brand” / “late-night infomercial but with premium typography”
- Create at: `/demos/petskinz`

## Pages
Only one page:
- `/demos/petskinz/index.basil`

No login, no register, no database required.

## Visual Layout (single page)
Design a responsive one-page marketing layout with these sections:

1) **Hero**
  - Big brand name: PetSkinz
  - Slogan: “Alive Again”
  - Subheadline: something like “Because grief deserves a second coat.”
  - CTA button scrolling to contact form: “Request an Estimate”
  - Small, humorous disclaimer text (non-legal): “This is a parody demo for Basil templating. Please do not mail anything to anyone.”

2) **“Stunning Results” Photo Gallery**
  - Grid of 8–10 “photo placeholders” (use local placeholder images or simple styled boxes if no images exist yet).
  - Each placeholder must include a caption that tells Erik what to AI-generate and what vibe it should be.
  - Captions should be printed on the page beneath each placeholder.

   Use THESE captions (make them editable in an array in Basil so Erik can tweak them):
  - “Golden retriever puppy wearing an older golden retriever’s exact markings; sunny yard; cinematic.”
  - “Owner hugging a ‘same’ cat — identical fur pattern; cozy living room; warm film grain.”
  - “Before/After split: ‘Mr. Pickles’ (then) vs ‘Mr. Pickles’ (Alive Again); same collar; glossy ad style.”
  - “French bulldog ‘Alive Again’ reveal party; confetti; everyone smiling a little too hard.”
  - “Close-up: perfectly matched tabby stripes; shallow depth of field; luxury pet shampoo commercial.”
  - “Kid holding ‘Alive Again’ bunny; soft pastel background; overly wholesome.”
  - “Older couple walking ‘Alive Again’ dachshund; golden hour; suburban sidewalk; premium brand vibes.”
  - “Veterinarian-looking person giving thumbs-up; ‘Alive Again’ pet on exam table; suspiciously clean.”
  - “Group photo: three ‘Alive Again’ pets lined up like a catalog shoot; white seamless backdrop.”
  - “Product shot: ‘PetSkinz Care Kit’ next to a sleeping ‘Alive Again’ pet; hyperreal ad style.”

3) **Testimonials (short quotes)**
  - Render from a Basil array using a loop.
  - Tone: delighted + horrified.
  - 10–14 items.

4) **FAQ**
  - Render from a Basil array of Q/A objects using a loop.
  - Must include: “Should I report this website to the police?”
  - 10–14 items.

5) **Contact Form (“Request an Estimate”)**
  - Fields:
    - Full name
    - Email
    - Pet name
    - Pet age (years)
    - Notes (textarea): “Tell us anything we should know… emotionally or medically.”
    - File upload: “Attach a photo of your pet (alive or otherwise)”
  - On submit:
    - Validate required fields (name, email, pet name, pet age).
    - Validate upload is optional but if provided must be an image type (jpg/png/webp) and max size (e.g. 6MB).
    - Save upload to a local demo folder (e.g. `/demos/petskinz/uploads/` with safe randomized filename).
    - Send an email via Basil SMTP to: `blackrushdrive@gmail.com`
    - Email subject: `PetSkinz Estimate Request: <PetName> (<Age>y)`
    - Email body should include all fields, plus saved filename/path.
    - If SMTP isn’t configured, show a friendly error message telling the developer what env vars are missing.

## Basil Requirements
- Use Basil templating blocks `<?basil ... ?>` for:
  - Arrays (testimonials, FAQ, gallery captions)
  - Loops that render each list
- Keep the Basil code readable and “tutorial-ish”
- Include comments in the Basil code explaining:
  - How arrays work
  - How the loop works
  - How form POST handling works
  - How file upload is processed
  - How SMTP is configured

## Config / Env
Create or document an `.env` for this demo (or reuse the demo site’s conventions if they exist):
- `PETSKINZ_SMTP_HOST`
- `PETSKINZ_SMTP_PORT`
- `PETSKINZ_SMTP_USER`
- `PETSKINZ_SMTP_PASS`
- `PETSKINZ_SMTP_FROM` (e.g. `PetSkinz <no-reply@petskinz.local>`)
- `PETSKINZ_CONTACT_TO` defaulting to `blackrushdrive@gmail.com`

If Basil already has an SMTP helper/module, use it. Otherwise implement using the existing Basil mail/SMTP functionality already in the project.

## File Structure
Create:
- `/demos/petskinz/index.basil`
- `/demos/petskinz/assets/` (CSS, placeholder images if needed)
- `/demos/petskinz/uploads/` (ensure it exists; add .gitignore to exclude uploads)

## Content: Testimonials Array (use these)
Include these as a Basil array of strings:

1. “It’s like he never left… except now he’s faster. And younger. And stares at me like a stranger. Five stars.”
2. “The fur is IDENTICAL. My therapist is concerned, but my heart is thrilled.”
3. “My husband cried, then screamed, then hugged the dog. Incredible customer journey.”
4. “We asked for ‘Alive Again’ and they delivered ‘Alive Again-ish.’ That’s honestly enough.”
5. “Same spots, same ears, same vibe. Different soul. No notes.”
6. “I feel comforted and mildly haunted. Which is… a comfort I didn’t know I needed.”
7. “Our cat is back. My conscience is not.”
8. “I can’t explain it, but the new hamster feels like it knows what we did.”
9. “My children think it’s magic. I think it’s a felony. We are bonding as a family.”
10. “The coat match is flawless. The moral match is… complicated.”
11. “I requested ‘exactly the same’ and they nailed ‘uncannily similar.’ A+ craftsmanship.”
12. “It’s both closure and a restart button I probably shouldn’t have pressed.”
13. “Customer service was cheerful in a way that made me question reality.”
14. “I reported the website, then I didn’t. Then I did again. Then I didn’t. Anyway: great work.”

## Content: FAQ Array (Q/A pairs)
Represent FAQ items as an array of objects/maps with `q$` and `a$` (or whatever object structure Basil likes).
Use these:

1. Q: “What is PetSkinz?”
   A: “A premium ‘continuity service’ that helps your heart move forward while your eyes insist nothing changed.”

2. Q: “How does ‘Alive Again’ work?”
   A: “We match a young, similar animal and create a ‘coat continuity’ experience. (This website is parody demo content.)”

3. Q: “Is this ethical?”
   A: “Ethics is a spectrum. Our branding is a rectangle.”

4. Q: “Will my pet have the same personality?”
   A: “Personality is not included in the pelt. Results vary emotionally.”

5. Q: “Does my new pet remember me?”
   A: “Memory not guaranteed. Attachment, however, is extremely likely.”

6. Q: “What pets do you support?”
   A: “Common domestic pets: dogs, cats, rabbits. If it has fur, we have… opinions.”

7. Q: “Is this safe?”
   A: “Physically: this is a parody website. Technically: the contact form works.”

8. Q: “Should I report this website to the police?”
   A: “If you believe a crime is occurring, contact local authorities. Also: this is satirical demo content.”

9. Q: “Do you offer refunds?”
   A: “We offer ‘emotional store credit’ in the form of a sincere thumbs-up.”

10. Q: “What do you need for an estimate?”
    A: “A photo (alive or otherwise), your pet’s name and age, and your best attempt at not thinking too hard about it.”

11. Q: “Do you return the original pet?”
    A: “This is a parody. Please do not mail anything to anyone.”

12. Q: “Can you match rare markings exactly?”
    A: “We aim for ‘uncannily close’ — the premium tier is ‘you will gasp.’”

13. Q: “Is this legal where I live?”
    A: “We cannot provide legal advice, but we can provide extremely confident typography.”

14. Q: “Why does this site exist?”
    A: “To demonstrate Basil templating loops and form handling with a memorable (disturbing) concept.”

## Implementation Notes
- Use semantic HTML and clean CSS (no frameworks required, but OK if the project already uses one).
- Keep everything in one file if easiest, but prefer:
  - `index.basil` + `assets/style.css`
- Provide a clear success state after form submission:
  - “Estimate request received. We will respond soon (emotionally).”
- Provide clear error states with friendly messages.

## Acceptance Criteria
- Page loads and looks polished on desktop + mobile.
- Gallery captions render from an array via loop.
- Testimonials render from an array via loop.
- FAQ renders from Q/A array via loop.
- Contact form POST works:
  - validates fields
  - handles optional image upload
  - sends SMTP email to `blackrushdrive@gmail.com` (or shows config error with env var list)
  - shows success message

Build it now in `/demos/petskinz`.
