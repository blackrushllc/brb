Yes — that structure feels exactly right:

* **Home page** for the polished public-facing pharma branding and Ophidiane push
* **About Gamora** for corporate culture, leadership, fake mission statements, “Life at Gamora,” Stebner, Nedry, Bella, group photos, and the eerie absence of the grandfather
* **Contact page** for the Basil-backed demo form

That gives it a believable company shape without making the site too big for a clean demo. It also lets the **Home page stay slick and sales-focused**, while the **About page carries the weird subtext**.

Here’s a strong **Junie prompt** you can drop in:

---

Create a small but polished **Basil demo website** for a fictional pharmaceutical company called **Gamora Pharmaceuticals**, intended as a public-facing promo site that can actually be deployed at **GamoraPharma.com** as part of the AtomicFlix / Atomic Zone universe.

This should be a **complete, working mini demo** with a real Basil backend for a contact form, but the primary goal is to create a **convincing fictional corporate pharma site** that feels glossy, expensive, slightly sinister, and darkly funny if you look closely.

## Goal

Build a 3-page website:

1. **Home**
2. **About Gamora**
3. **Contact**

The site should feel like a strange blend of:

* polished corporate biotech / pharmaceutical branding
* legacy prestige company energy
* subtle satire
* a faintly unsettling “something is wrong here” undertone
* appropriate for a fictional company from the Atomic Zone universe

The visitor should be able to browse it as if it were a real company website, while fans of the show will recognize that Gamora is obviously shady.

## Important high-level direction

This is for a **Basil demo series**, so please make it a **good Basil showcase**, not just static HTML.

Use Basil features where appropriate:

* shared layout
* reusable partials/components
* page data or route-driven content where helpful
* a working contact form POST handler
* success/error flash messaging
* simple validation
* neat clean project organization
* examples/docs if helpful

Do not worry about tests unless explicitly needed.

## Site architecture

Please create a small site with these pages/routes:

* `/` → Home
* `/about` → About Gamora
* `/contact` → Contact
* optional POST route for contact submission, such as `/contact/submit`

## Desired tone and story subtext

Gamora Pharmaceuticals is a fictional company with a flagship psychiatric drug called **Ophidiane**.

The public-facing site should present Ophidiane as:

* elegant
* safe
* trustworthy
* clinically advanced
* emotionally stabilizing
* intended for depression / agitation / mood instability

But the writing should also contain subtle satire and corporate creepiness:

* vague claims dressed up as science
* “stability” framed almost too lovingly
* emotionally flattening language
* suspiciously polished phrases
* a sense that the company values compliance, calmness, and acceptance over actual human flourishing

This should not become campy parody everywhere. Keep most of it believable, with only a few details being “off” in an eerie way.

## Visual style

Design a polished fictional corporate pharma website with:

* modern clean layout
* premium pharma / biotech aesthetic
* cool whites, soft grays, muted blues, maybe pale teal
* subtle gradients
* clean cards and sections
* tasteful hero banners
* corporate headshots / image placeholders
* sections for product, leadership, research, workplace culture
* responsive design
* professional typography
* no dependency on JS-heavy frameworks unless really needed

The site should feel deployable as a clean promotional site for a suspiciously respectable company.

## Content requirements

### 1. Home page

The home page should include:

#### Hero section

* Gamora Pharmaceuticals branding
* headline introducing the company
* secondary emphasis on **Ophidiane**
* CTA buttons such as:

    * Learn About Ophidiane
    * About Gamora
    * Contact Us

#### Ophidiane flagship product section

Include a polished product spotlight for **Ophidiane**.

Possible brand direction:

* “Steady Is Beautiful”
* “For a calmer outlook”
* “A smoother way to feel”
* “Helping restore emotional balance in a demanding world”

Include:

* product description
* a few “benefits” cards
* a mild disclaimer / safety note area
* a tasteful product bottle mockup area or image placeholder
* maybe a “why physicians trust Ophidiane” section

Do not make medical claims so specific that it becomes silly. Keep it plausible and softly eerie.

#### Trust / research / innovation section

Include some typical corporate pharma material:

* commitment to research
* patient-centered care
* rigorous standards
* innovation in emotional wellness
* maybe numbers/stats blocks, but clearly fictional/demo-safe

#### Featured culture teaser

A small teaser leading to the About page:

* leadership
* life at Gamora
* research excellence
* company values

### 2. About Gamora page

This page should do a lot of the worldbuilding work.

Include sections such as:

#### Company overview

* history of Gamora Pharmaceuticals
* mission
* vision
* values
* polished but slightly odd corporate language

#### Leadership section

Create profile blocks/placeholders for:

* **Nedry Gamora** — executive leadership / strategy / corporate development
* **Bella Gamora** — brand leadership / public engagement / wellness initiatives
* **Dr. Stebner** — chief scientist / head of research / neurochemical innovation

Important subtext:

* Nedry and Bella should appear overpromoted and suspiciously glamorous
* Stebner should sound like the real brain in the room
* the grandfather / true old power behind the company should be conspicuously absent and never explained

#### Life at Gamora

Create a corporate culture section with:

* team photos
* lab photos
* office candid placeholders
* values blurbs
* references to collaboration, excellence, stability, stewardship, innovation

This section should be especially useful for later adding your own fake photos from the show.

Please include placeholders/captions for:

* corporate office candid images
* lab team images
* leadership photos
* a group company photo

Also include a spot where the user could later place a group image containing:

* Junior
* Nadine
* Stebner
* assorted scientists
* 80s corporate jerk types

#### Careers / workplace culture teaser

Could be fictional, not necessarily a full jobs board. Just enough to make the company seem real.

### 3. Contact page

The contact page should be a real Basil demo feature.

Include:

* polished contact form
* fields like:

    * name
    * email
    * organization
    * subject
    * message
* optional department selector:

    * General Inquiry
    * Media Relations
    * Research Partnerships
    * Product Information
    * Careers

Backend requirements:

* real Basil form handling
* validation
* sanitize inputs
* success message on submit
* error display on invalid fields
* either:

    * store submissions to a simple file, or
    * send email if easy and already idiomatic in Basil, or
    * just log/store locally in a simple demo-friendly way

Please keep it simple and reliable.

Also add:

* a fake corporate address
* a phone number
* a generic media email / info email placeholder
* business hours if desired

## Asset and placeholder strategy

Please design the templates so that image assets can easily be swapped later.

Use clearly named placeholders or image references for things like:

* Ophidiane product bottle image
* Nedry headshot
* Bella headshot
* Dr. Stebner headshot
* “Life at Gamora” office candid photos
* lab research photos
* team group photo

Use clean filenames and folders so I can replace them later with real mockups or stills from the Atomic Zone episode.

Example asset structure ideas:

* `/public/assets/img/leadership/nedry.jpg`
* `/public/assets/img/leadership/bella.jpg`
* `/public/assets/img/leadership/stebner.jpg`
* `/public/assets/img/culture/life-at-gamora-1.jpg`
* `/public/assets/img/culture/lab-team.jpg`
* `/public/assets/img/product/ophidiane-bottle.png`
* `/public/assets/img/company/group-photo.jpg`

## Basil implementation preferences

Please structure this like a tidy Basil example/demo project.

Use:

* shared site layout
* header/nav/footer partials
* clean route/page organization
* a small config/data file if useful for company text or leadership bios
* simple, readable Basil templates
* comments in key places so this also serves as a learning example

If Basil has a preferred style for:

* layout includes
* form handling
* posting and reading flash/session state
* data dictionaries passed into RENDER$
* FRED directives

please follow those idioms.

## Navigation

Top nav should include:

* Home
* About Gamora
* Contact

Footer can include:

* copyright
* fictional disclaimer if you think that is wise
* quick links
* product/legal-ish links if helpful

## Optional nice touches

If easy, include a few subtle details that reward close inspection:

* weirdly euphemistic wording about emotional “stability”
* a line or two that sounds too interested in compliance or acceptability
* an overly polished safety/disclaimer block
* corporate language that sounds good at first but grows stranger on reflection

Keep this tasteful and sparse. The site should still mostly pass as believable.

## Deliverables

Please produce:

1. the full Basil demo site implementation
2. all templates/pages/routes needed
3. any supporting data/config files
4. placeholder assets or references
5. a short README explaining:

    * how to run it
    * where to swap images
    * how the contact form works
    * where submissions are stored

Also include at least one small example of sample submitted data or a note on where it will appear.

## Naming / branding reminders

Use the exact company/domain/product names:

* **Gamora Pharmaceuticals**
* **GamoraPharma.com**
* **Ophidiane**

Leadership characters:

* **Nedry Gamora**
* **Bella Gamora**
* **Dr. Stebner**

Additional company/world flavor may lightly reference:

* research staff
* assistants
* team members
* a larger organization
* but do not directly explain the hidden sinister lore

## Final note

This should feel like:
“a legitimate polished demo website for a fictional pharmaceutical company that just happens to be quietly terrifying.”

Prioritize elegance, credibility, and clean Basil example structure over excessive complexity.

---

A couple of creative notes from me:

Putting **Corporate Culture on the About page** is better than splitting it off. It keeps the site compact and believable. A tiny pharma promo site with too many sections starts to feel fake in the wrong way.

Also, the **missing grandfather** is a great touch. Do not explain it. That absence will do a lot of work.

I can also make you:

* a **shorter, more forceful Junie prompt**
* a **site map + wireframe outline**
* or the actual **page copy text** for Home, About, and Contact so Junie has less writing to invent.
