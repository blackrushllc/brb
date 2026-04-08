## Goal

Build a 3-page website:

1. **Home**
2. **About Gamora**
3. **Contact**

The website will be in /demos/gamora

All paths should be relative because this will not be in the root of a real site although it could be moved to one.

I have created gamora/images/ with some sub folders for images described later in this document.

* **Home page** for the polished public-facing pharma branding and Ophidiane push
* **About Gamora** for corporate culture, leadership, fake mission statements, “Life at Gamora,” Stebner, Nedry, Bella, group photos, and the eerie absence of the grandfather
* **Contact page** for the Basil-backed demo form

That gives it a believable company shape without making the site too big for a clean demo. It also lets the **Home page stay slick and sales-focused**, while the **About page carries the weird subtext**.

Here’s a strong **Junie prompt** you can drop in:

---

Create a small but polished **Basil demo website** for a fictional pharmaceutical company called **Gamora Pharmaceuticals**, intended as a public-facing promo site that can actually be deployed at **GamoraPharma.com** as part of the AtomicFlix / Atomic Zone universe.

This should be a **complete, working mini demo** with a real Basil backend for a contact form, but the primary goal is to create a **convincing fictional corporate pharma site** that feels glossy, expensive, slightly sinister, and darkly funny if you look closely.


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

Here are the image assets to use. All images are 1024x1024 unless otherwise noted in the filename:

Head shots are in images/team
"Corporate Culture" images are in images/culture
Lab photos are in images/lab
Office candid photos are in images/office
Product images are in images/product




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


Absolutely. Here’s polished **actual page copy** you can hand to Junie, along with a set of **image-generator prompts** for the fake 1980s-style pharma visuals.

I wrote this to feel like a **believable glossy pharma site**, with just enough Gamora creep under the paint.

---

# Home Page Copy

## Hero

**Gamora Pharmaceuticals**

### Advancing emotional wellness for a more balanced tomorrow.

At Gamora Pharmaceuticals, we believe modern life demands modern solutions. Through patient-centered research, clinical rigor, and a commitment to innovation, we develop therapies designed to support steadier outcomes in a demanding world.

**Introducing Ophidiane®**
A prescription therapy for patients experiencing depressive mood disturbance, agitation, and mood instability.

**Steady Is Beautiful.**

**Buttons:**

* Learn About Ophidiane
* About Gamora
* Contact Us

---

## Welcome Section

### A legacy of confidence in complex times

For decades, Gamora Pharmaceuticals has pursued one mission: to help patients and providers navigate the growing challenges of emotional health with confidence, calm, and clarity.

Our teams bring together scientific insight, operational excellence, and a forward-looking approach to therapeutic innovation. The result is a portfolio centered on trust, consistency, and outcomes that matter in everyday life.

---

## Ophidiane Product Spotlight

### Meet Ophidiane®

In an increasingly demanding world, emotional strain can affect every aspect of daily life. Feelings of sadness, irritability, overstimulation, agitation, and instability may place a burden on individuals, families, and routines.

**Ophidiane®** is Gamora Pharmaceuticals’ flagship prescription therapy developed to help restore a smoother, more manageable emotional experience in appropriate patients.

Designed for those experiencing depressive mood disturbance accompanied by agitation or mood instability, Ophidiane helps support:

* A calmer daily outlook
* Reduced emotional overreaction
* Greater steadiness across changing conditions
* Improved comfort with ordinary routines
* A more balanced sense of well-being

### Why physicians trust Ophidiane

Providers choose Ophidiane for its refined therapeutic profile, dependable tolerability, and role in supporting a more even emotional baseline for patients facing modern stressors.

Where emotional peaks and valleys disrupt daily life, Ophidiane helps patients move toward a steadier tomorrow.

**Tagline block:**

## Ophidiane®

### For a calmer outlook. For a steadier tomorrow.

---

## Promotional Slop Section

### Because balance matters

Not every struggle is visible. Emotional strain can appear in subtle ways: tension during everyday interactions, difficulty adapting to change, unpredictable lows, or periods of overstimulation that interfere with work, family, and peace of mind.

Ophidiane was developed with one goal in mind: to help patients experience life more smoothly, with fewer disruptive fluctuations and greater ease in the moments that matter most.

When emotional life becomes harder to manage, a more stable path forward may be closer than you think.

### Ask your physician whether Ophidiane may be right for you.

---

## Benefits Cards

### Smoother Days

Supports a more even emotional experience from morning to evening.

### Greater Stability

Helps soften disruptive peaks and reduce difficult lows.

### Everyday Function

Designed to support comfort, routine, and continuity in daily life.

### Trusted Innovation

Backed by Gamora’s ongoing investment in neurochemical research.

---

## Research / Trust Section

### Guided by research. Built on standards.

At Gamora Pharmaceuticals, our work is grounded in disciplined development, responsible testing, and a belief that better emotional health begins with better therapeutic tools.

We continue to invest in advanced neurochemical research, patient-centered design, and precision-guided innovation across every phase of development.

**Optional stat blocks for fake corporate metrics:**

* 40+ Years of research excellence
* 12 Global research initiatives
* 1 Flagship commitment to emotional wellness
* Countless lives supported through therapeutic progress

---

## Safety / Fine Print Section

### Important Safety Information

Ophidiane® is a prescription therapy and is not appropriate for every patient. As with any medication, treatment decisions should be made in consultation with a qualified physician.

Patients should discuss all current medications, medical history, and treatment goals with their healthcare provider before beginning therapy.

**Soft creepy version of fine print:**
Some patients may experience drowsiness, dry mouth, vivid dreams, reduced emotional intensity, slowed response time, memory fog, or changes in appetite or weight. In rare cases, unusual calmness, affective flattening, or changes in personality may occur. Patients should speak with a physician if symptoms worsen, persist, or begin to feel unfamiliar.

---

## Culture Teaser

### The people behind the promise

From executive leadership to research and operations, the Gamora team is united by a shared belief in structure, excellence, and progress.

Meet the minds helping shape the future of emotional wellness.

**Button:**

* About Gamora

---

## Footer Copy

Gamora Pharmaceuticals is committed to responsible therapeutic innovation, patient-centered research, and stronger outcomes through science.

**Footer links:**

* Home
* About Gamora
* Contact
* Product Information
* Research
* Privacy
* Terms

**Tiny fictional disclaimer:**
This website is intended for informational purposes only and does not provide medical advice.

---

# About Page Copy

## Hero

# About Gamora

### Innovation, trust, and therapeutic confidence for a changing world

Gamora Pharmaceuticals is dedicated to advancing therapies that help patients move through life with greater stability, confidence, and continuity.

---

## Company Overview

### Our story

Gamora Pharmaceuticals was built on a simple belief: that scientific progress should not only extend life, but improve the quality of living it.

Over the years, our company has grown into a multidisciplinary organization spanning research, development, operations, communications, and patient engagement. While our capabilities have expanded, our purpose has remained the same: to create therapies that help people experience life in a more manageable and sustainable way.

Today, Gamora is recognized for its commitment to emotional wellness, neurochemical innovation, and the disciplined pursuit of therapeutic progress.

---

## Mission / Vision / Values

### Our mission

To develop therapies that promote steadier, more supportive outcomes in emotional and behavioral health.

### Our vision

A world in which patients, providers, and families can move forward with greater confidence, calm, and continuity.

### Our values

**Integrity**
We pursue excellence with discipline and discretion.

**Innovation**
We believe better outcomes begin with better questions and better science.

**Stewardship**
We value order, responsibility, and long-term thinking.

**Stability**
We believe well-being is strengthened through consistency, resilience, and balance.

**Collaboration**
We bring together diverse expertise in service of a common therapeutic future.

---

## Leadership Section

## Leadership

### Nedry Gamora

**Executive Director, Corporate Strategy**

Nedry Gamora helps shape the company’s public direction, strategic partnerships, and long-range growth initiatives. Known for his polished leadership style and strong instinct for emerging opportunities, Nedry plays an active role in advancing the Gamora vision across markets and audiences.

### Bella Gamora

**Director of Brand and Public Wellness Initiatives**

Bella Gamora leads public-facing engagement across brand identity, communications strategy, and wellness-centered messaging. Her work emphasizes trust, clarity, and the importance of making therapeutic progress feel accessible, reassuring, and relevant to modern families.

### Dr. Stebner

**Chief Scientist, Neurochemical Research**

Dr. Stebner leads Gamora’s scientific initiatives in neurochemical stabilization and therapeutic design. His work has helped define the company’s research direction in emotional wellness and has played a central role in the development philosophy behind Ophidiane and other future-facing programs.

**Tiny optional subtext line:**
Together, Gamora’s leadership reflects a unified commitment to scientific innovation, therapeutic elegance, and a more stable future.

---

## Research Section

### Science at the center

Our research teams work across laboratory, clinical, and translational settings to better understand the chemistry of emotional regulation and the therapeutic pathways that support healthier outcomes.

At Gamora, we believe that effective treatment is not only about symptom reduction. It is about helping individuals achieve steadier engagement with the structures of daily life.

Our current focus areas include:

* Mood instability and emotional regulation
* Neurochemical pathways related to agitation and affect
* Long-term therapeutic tolerability
* Patient-centered treatment experiences
* Next-generation tools for emotional wellness

---

## Life at Gamora

## Life at Gamora

### Excellence begins with people

At Gamora Pharmaceuticals, our culture reflects the same values that guide our science: focus, discipline, collaboration, and a belief in meaningful progress.

Across our offices, labs, and shared spaces, teams work together to support a mission that reaches far beyond the workplace. Whether in research meetings, production planning, community initiatives, or day-to-day collaboration, Gamora people bring structure, care, and purpose to everything they do.

**Suggested image captions / placeholder copy:**

**Leadership in Motion**
A look inside Gamora’s executive culture and strategic planning environment.

**Research Excellence**
Scientists and support teams collaborating across key therapeutic initiatives.

**Everyday at Gamora**
Moments from daily life across our offices, labs, and shared workspaces.

**Team Culture**
Celebrating the people whose work helps move therapeutic innovation forward.

**Company Gathering**
A group moment highlighting the broader Gamora team across departments and disciplines.

---

## Corporate Culture Promo Slop

### A workplace built on confidence and continuity

We believe strong outcomes begin with strong teams. That is why Gamora fosters an environment shaped by mutual respect, high standards, and a shared dedication to therapeutic progress.

Our people are encouraged to think clearly, act responsibly, and contribute to a culture where consistency and excellence are valued at every level.

From the lab bench to the boardroom, we are building more than medicines. We are building trust.

---

## Careers Teaser

### Build what comes next

Gamora Pharmaceuticals is always interested in connecting with individuals who are passionate about science, therapeutic innovation, and meaningful impact.

We seek thoughtful professionals who value discipline, collaboration, and the opportunity to contribute to a steadier future.

**Button:**

* Contact Our Team

---

## About Footer Line

Gamora Pharmaceuticals remains committed to advancing emotional wellness through research, responsibility, and refined therapeutic design.

---

# Contact Page Copy

## Hero

# Contact Gamora

### We welcome inquiries from patients, providers, partners, and members of the media

Whether you are seeking product information, partnership opportunities, media materials, or general company details, the Gamora team is here to help direct your inquiry.

---

## Intro Copy

Please use the form below to contact the appropriate department. A member of our team will review your message and respond as soon as possible.

For urgent medical questions, please consult a licensed physician.

---

## Contact Form Labels

### Contact Form Heading

**Send Us a Message**

**Fields:**

* Full Name
* Email Address
* Organization
* Department
* Subject
* Message

**Department options:**

* General Inquiry
* Product Information
* Media Relations
* Research Partnerships
* Careers

**Button:**

* Submit Inquiry

---

## Form Success Message

### Thank you for contacting Gamora Pharmaceuticals.

Your inquiry has been received and routed to the appropriate department. A member of our team will follow up as soon as possible.

---

## Form Error Message Copy

### Please review the highlighted fields.

Some required information appears to be missing or invalid. Kindly correct the form and resubmit your inquiry.

---

## Contact Details Block

## Corporate Contact Information

**Gamora Pharmaceuticals**
1250 Meridian Plaza
Suite 800
New Haven, CT 06510

**Phone:** (203) 555-0184
**Email:** [info@gamorapharma.com](mailto:info@gamorapharma.com)
**Media:** [media@gamorapharma.com](mailto:media@gamorapharma.com)

**Business Hours:**
Monday–Friday
9:00 AM – 5:30 PM Eastern

---

## Side Promo Block on Contact Page

### Questions about Ophidiane?

Our team can provide general product information, media materials, and corporate background related to Gamora Pharmaceuticals and its therapeutic programs.

For prescribing decisions, treatment guidance, or questions about side effects, patients should always consult a qualified healthcare provider.

**Mini tag block:**
**Ophidiane®**
For a calmer outlook. For a steadier tomorrow.

---

# Extra Ophidiane Ad Copy Blocks

These can be dropped anywhere on the Home page, sidebars, cards, or banners.

## Short slogan options

* **Steady Is Beautiful.**
* **A smoother way to feel.**
* **For a calmer outlook.**
* **Because balance matters.**
* **Helping restore emotional balance in a demanding world.**
* **When life feels too sharp, choose something softer.**
* **Support for a steadier sense of self.**
* **Therapeutic confidence for complex emotional lives.**

## Fake ad paragraph 1

There are times when emotional life can become difficult to navigate. Stress, sadness, agitation, and instability may quietly affect relationships, routines, and the way each day is experienced. Ophidiane® was developed to help appropriate patients move toward a more balanced emotional baseline with greater comfort and consistency.

## Fake ad paragraph 2

Modern life asks a great deal of the human nervous system. Ophidiane helps support patients facing depressive mood disturbance and emotional instability by promoting a calmer, more manageable daily experience.

## Fake ad paragraph 3

Not every burden leaves a visible mark. Sometimes the struggle is internal, cumulative, and hard to name. With Ophidiane, patients may find a steadier path forward and renewed ease in the rhythms of everyday life.

## Mildly unsettling block

At Gamora, we understand that well-being is often supported not by intensity, but by balance. Not by disruption, but by steadiness. Not by extremes, but by a more sustainable emotional pattern.

---

# Image Generator Prompts

Here are prompts you can feed to an image generator for **authentic 1980s pharma ad visuals**.

## 1. Ophidiane bottle product shot

**Prompt:**
1980s pharmaceutical advertisement product shot, a prescription pill bottle labeled Ophidiane, elegant vintage antidepressant branding, glossy magazine ad style, soft studio lighting, pale blue and cream color palette, subtle gold accents, clean white background with faint gradient, authentic 1980s corporate pharma aesthetic, polished and reassuring, premium medical ad photography, square composition, no modern design elements, readable label, cinematic realism

---

## 2. Happy family pharma ad

**Prompt:**
1980s pharmaceutical ad, smiling upper middle class family in a bright suburban kitchen, soft sunlight through curtains, mother holding coffee, father in business shirt and tie, child laughing nearby, glossy antidepressant magazine ad look, warm reassuring mood, slightly artificial corporate happiness, authentic 1980s print photography, pastel tones, soft focus, premium drug advertisement aesthetic

---

## 3. Woman at window “before treatment” image

**Prompt:**
1980s pharmaceutical commercial still, elegant woman in a cream sweater standing by a rainy window in a quiet suburban home, reflective and emotionally distant mood, soft cinematic lighting, authentic 1980s antidepressant ad style, tasteful, glossy, premium print magazine aesthetic, muted pastel colors, realistic photography

---

## 4. “After treatment” grocery store image

**Prompt:**
1980s pharmaceutical advertisement, calm smiling woman walking through a grocery store aisle, soft golden lighting, polished vintage antidepressant ad style, subtle fake happiness, premium corporate medical ad photography, authentic 1980s wardrobe and hair, pastel tones, clean reassuring mood

---

## 5. Doctor office ad image

**Prompt:**
1980s doctor office scene, wood paneled walls, framed diplomas, male physician in conservative suit and white coat writing a prescription, female patient listening with hopeful expression, authentic 1980s pharmaceutical commercial look, glossy premium ad photography, warm muted colors, believable vintage medical setting

---

## 6. Corporate Gamora leadership portrait

**Prompt:**
1980s corporate pharmaceutical executive portrait, glamorous young male executive in expensive suit, polished smile, biotech company leadership headshot, slightly smug energy, soft studio lighting, authentic 1980s corporate annual report aesthetic, realistic photography, premium magazine quality

Use a matching version for Bella:
**Prompt:**
1980s corporate pharmaceutical executive portrait, glamorous young female executive in elegant power suit, polished smile, biotech company leadership headshot, expensive jewelry, confident corporate energy, soft studio lighting, authentic 1980s annual report aesthetic, realistic photography, premium magazine quality

---

## 7. Dr. Stebner scientist portrait

**Prompt:**
1980s research scientist portrait, brilliant but unsettling pharmaceutical chief scientist in a lab coat standing in a private laboratory, dim corporate lab lighting, serious expression, intelligent intense eyes, authentic 1980s biotech photography, realistic, glossy annual report style, cinematic but believable

---

## 8. Life at Gamora office candid

**Prompt:**
1980s corporate office candid photo, pharmaceutical employees in business attire collaborating in a bright office, paperwork, glass walls, beige computers, subtle corporate culture propaganda feel, authentic 1980s company brochure photography, polished but slightly eerie, realistic, premium print quality

---

## 9. Lab team photo

**Prompt:**
1980s pharmaceutical laboratory group photo, scientists and technicians in white lab coats standing together in a clean research lab, corporate brochure style, authentic vintage biotech aesthetic, fluorescent lab lighting, serious but proud expressions, premium print ad realism

---

## 10. Group company photo with awkward energy

**Prompt:**
1980s pharmaceutical company group photo, mix of executives, scientists, assistants, and office staff posing in a corporate atrium, a few people smiling too hard, one shy mailroom clerk, one timid assistant, glossy annual report photography, authentic 1980s corporate culture image, polished but subtly unsettling, realistic

---

## 11. Full-page Ophidiane print ad layout image

**Prompt:**
full page 1980s antidepressant magazine advertisement for fictional drug Ophidiane, elegant smiling woman seated in soft morning light, prescription pill bottle in foreground, glossy pharmaceutical print layout, premium corporate typography area, pale blue and cream palette, reassuring but faintly sinister mood, authentic vintage medical ad design, realistic photography

---

## 12. TV commercial freeze-frame prompt

**Prompt:**
1980s television commercial freeze frame for fictional prescription antidepressant Ophidiane, smiling family at dinner table, soft golden light, broadcast commercial composition, slightly washed vintage video look, corporate pharmaceutical advertising aesthetic, realistic, emotionally artificial but polished

---

# Optional On-Image Ad Lines

These are useful if you want text baked into posters or page banners:

* **Ophidiane® — Steady Is Beautiful**
* **For a calmer outlook**
* **Helping restore emotional balance**
* **A smoother way to feel**
* **Because balance matters**
* **Ask your doctor about Ophidiane**
* **Modern support for modern emotional strain**
* **When life feels out of step, choose steadier ground**

---

# My recommendation

For the site itself, keep most of the imagery as:

* smiling family
* doctor office
* bottle shot
* lab team
* executive portraits
* one group company photo

That gives it the right fake-legit structure.

For **About Gamora**, the funniest and creepiest effect will come from very normal corporate captions paired with slightly off photos.







A couple of creative notes from me:

Putting **Corporate Culture on the About page** is better than splitting it off. It keeps the site compact and believable. A tiny pharma promo site with too many sections starts to feel fake in the wrong way.

