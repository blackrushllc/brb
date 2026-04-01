Junie —

Please build a full Basil demo application called TICKETHO in this repo, using Basil pages with <?basil ?> templating where appropriate, plus a backend API for async actions. Base the architecture, auth flow, session handling, database patterns, and general site conventions on /demos/website in this project repo. Reuse the same style of user management and project organization wherever it makes sense, but adapt it to this product.

This is a fun but real-ish educational demo site. The tone of the public site should be friendly, modern, helpful, and slightly whimsical — polished enough to feel like a legitimate free product, but still clearly part of the Syndorela ecosystem and educational initiative.

High-level product idea:
TICKETHO is a lightweight team-based ticket / task / issue intake and management platform. It supports teams, roles, ticket creation, status workflows, basic notifications groundwork, and future expansion. It is free and provided as part of the educational initiative from the Syndorela Kingdom. The public landing page should say that plainly and link to https://syndorela.com.

IMPORTANT:
This is not just “tasks for logged-in staff.” We also need a carefully designed reporter intake flow:

1. A team admin can generate a team-specific public intake URL.
2. A visitor hitting that URL does NOT immediately see a plain anonymous ticket form.
3. Instead, they fill out a registration / confirmation form first.
4. The system emails them an auto-login confirmation link.
5. Clicking that link confirms their email, logs them in automatically, and sends them to the actual “new ticket” form.
6. That new ticket form is associated with the team implied by the original intake URL.
7. If no team-specific intake URL is used, or if a generic public entry point is used, tickets should go to the default team defined in .env.
8. Reporter must be logged in to post.
9. New intake users join the relevant team in a restricted “reporter” role.
10. Reporter role can create tickets and view only their own tickets, read-only after creation unless we explicitly allow limited edits early in the flow.
11. Team admin can later elevate that user from reporter to member.
12. We will add custom task forms later, so design the code and DB in a way that won’t fight future per-team custom intake forms.

I want this implemented as a proper demo inside the repo, not as a vague mockup.

==================================================
PROJECT LOCATION / STRUCTURE
==================================================

Create the demo at:

/demos/ticketho

Follow the style and conventions already used in /demos/website as much as reasonably possible:
- page layout patterns
- auth/session patterns
- routing approach
- migrations / DB bootstrapping style used in this repo
- reusable template partials
- user management conventions
- any shared utilities already used by the demo sites

Please inspect /demos/website first and model this after it rather than inventing an entirely different app shape.

==================================================
TECH + IMPLEMENTATION REQUIREMENTS
==================================================

Use:
- Basil pages and <?basil ?> templating where applicable
- server-rendered pages for the main UX
- a backend API for actions that benefit from async / JS calls
- lightweight JavaScript only where useful
- clean, readable CSS / existing demo styling conventions
- MySQL or the project’s normal DB target
- environment-driven config via .env
- no giant JS framework

Keep it approachable and educational. This should feel like a good demo of what Basil templating + app logic can do.

==================================================
BRANDING / PRODUCT POSITIONING
==================================================

Product name:
TICKETHO

Public site should present it as:
- free
- useful
- team-based
- easy to onboard with
- part of the Syndorela Kingdom educational initiative
- linked to Syndorela.com

The landing page should have:
- hero section
- features section
- “How it works” section
- “Why it’s free” / educational initiative section
- “Coming Soon” section
- login/register CTAs
- a team intake / submit-a-ticket entry point
- tasteful mention that the system can eventually support notifications and reply-based updates

==================================================
PAGES TO BUILD
==================================================

Please create at least these pages / routes, adapting names to existing repo conventions if needed:

Public / marketing:
- home / landing page
- features section on the home page
- how-it-works section
- coming-soon section
- login page
- register page
- forgot password page
- reset password page
- public intake start page
- public intake landing page for a specific team via generated team URL
- email-confirm / auto-login landing route
- logged-out confirmation page as needed

Authenticated user pages:
- user_home / dashboard
- my tickets page
- ticket detail page
- create ticket page
- profile page
- profile avatar upload/edit page
- password change page
- team switcher page if multi-team membership is supported in the UI
- reporter-facing read-only ticket page(s)

Team admin pages:
- team dashboard
- team settings
- team members list
- member role management page / modal
- invitation links page
- team public intake links page
- statuses management page
- ticket management page
- ticket detail / edit page
- notification settings groundwork page
- audit-ish activity placeholder if easy
- admin-generated intake URL management UI

Owner/admin utility pages:
- create team
- edit team
- manage team public slug/token URLs
- promote reporter to member
- create invitation links
- revoke invitation links
- manage provider placeholders

Optional but nice:
- print-friendly ticket view
- mobile mini-page for quick status viewing
- empty-state illustrations / nice messages

==================================================
ROLES / PERMISSIONS
==================================================

Implement roles clearly and consistently:

- owner
  Full team control.

- admin
  Can manage team members, intake URLs, statuses, tickets, and settings.

- member
  Can work tickets normally for their team.

- reporter
  Restricted role for end users who came in through the intake flow.
  Can:
    - create tickets for the team they joined through
    - view only their own tickets
    - access their own profile
    - see read-only ticket history/details for their own tickets
      Cannot:
    - browse all team tickets
    - edit team settings
    - manage statuses
    - manage members
    - elevate anyone
    - access admin pages

Important:
A team admin must be able to elevate a reporter to member status later. This should be a simple admin action in the team members UI.

==================================================
INTAKE / REGISTRATION FLOW
==================================================

This is the heart of the new requirement.

Implement two public entry modes:

A) Generic public intake
- Example route: /intake or /submit-ticket
- If used without a team-specific token/slug, it should associate the eventual ticket with the default team from .env.

B) Team-specific intake
- Admin generates public intake URL for their team.
- Example patterns:
  /t/{team_slug}/new
  /join/{intake_token}
  /intake/{public_token}
- You choose the best structure, but make it clean and future-friendly.
- Team-specific URL must be generated by admin in the UI.
- If a valid team-specific URL is used, registration and the eventual new ticket form should be bound to that team.

Flow details:
1. Visitor arrives on intake URL.
2. They see a registration / confirmation form asking for:
    - full name
    - phone
    - email
3. They submit form.
4. System creates or updates a pending user/intake record.
5. System sends email containing a secure auto-login confirmation link.
6. User clicks link.
7. Email is marked confirmed.
8. User is logged in automatically.
9. User is added to the relevant team as reporter (or to default team if generic intake).
10. User is redirected directly to the actual new-ticket page.
11. They submit ticket.
12. They can later log in again and view only their own tickets.

Important behavior:
- Existing users who are already logged in and hit an intake URL can skip the email loop if appropriate, but still must be associated with the target team correctly.
- Existing users not logged in should still go through the email link flow for confirmation / magic login.
- Make the confirmation link double as both email verification and login.
- Use secure, time-limited tokens.
- Keep the implementation simple, secure, and educational.

==================================================
AUTH / ACCOUNT FEATURES
==================================================

Implement account features similar to the other demo sites, based on /demos/website:

- register
- login
- logout
- forgot password
- reset password
- session auth
- profile management
- email verification via magic confirmation/login link
- name / phone / email profile fields
- avatar upload
- role-aware navigation

Avatar requirements:
- image upload support for user profile avatar
- validate MIME type
- enforce reasonable file size limit
- constrain to 512x512 max output
- ideally resize/crop or normalize server-side if practical
- store path in DB
- display avatar in navbar/profile/team member listings where appropriate
- default avatar fallback if none uploaded

==================================================
DEFAULT TEAM REQUIREMENT
==================================================

We need a default team pre-initialized in the migration / seed process.

Also:
- add DEFAULT_TEAM_ID to .env
- the system should read the default team ID from .env
- generic public intake falls back to this default team
- if we want to change the default team later, changing .env should make that possible without rewriting code

Design the DB/migration so this is practical.

Because the current starter migration may assume every team has an owner, you may need to adjust the schema or seed logic to support a pre-initialized default team cleanly. Pick a sensible implementation:
- either allow a nullable/system owner for the default team
- or create a seeded system owner account
  Choose the cleaner approach for this demo and document it in the README.

==================================================
DATABASE / MIGRATION WORK
==================================================

Start from the existing TICKETHO migration ideas, but adapt them to this new Basil app and new workflow.

Please create or update migrations/tables as needed. Likely tables/entities include:

users
- id
- name
- email
- password_hash if standard login retained
- phone
- avatar_path
- email_verified_at
- secret_login_token or use dedicated token tables
- created_at / updated_at

teams
- id
- owner_id or nullable/system owner strategy
- name
- slug if useful
- created_at / updated_at

team_members
- team_id
- user_id
- role enum: owner/admin/member/reporter
- joined_at
- maybe invited_by / promoted_by if useful

tickets (or tasks if you keep that name internally, but user-facing language should be “tickets”)
- id
- team_id
- reporter_user_id
- title
- description
- status_id
- approved_by / handled_by if useful
- notes
- estimate
- time_spent
- created_at / updated_at / deleted_at

statuses
- global defaults
- team-specific custom statuses
- name
- color

invitations
- admin/team invite links for normal team joining

public_intake_links
- id
- team_id nullable if generic/default flow supported separately
- token and/or slug
- label / description
- active flag
- created_by
- created_at
- optional expires_at

email_login_tokens (or equivalent)
- user_id
- token
- purpose (confirm_email, login, intake_confirm, password_reset, etc. if unified)
- team_id nullable if needed for redirect context
- redirect_target or context payload if useful
- expires_at
- used_at
- created_at

team_settings
- provider stubs/configuration placeholders

usage_logs
- for future email/SMS usage tracking groundwork

Optional helpers:
- ticket_activity
- ticket_comments placeholder
- system_settings
- upload metadata

Seed:
- default statuses
- default team
- maybe a system owner if needed

Also update any existing starter migration logic accordingly rather than blindly copying it.

==================================================
API ENDPOINTS
==================================================

Add a backend API for actions that make sense. Keep it simple, clean, and documented.

Likely endpoints:
- auth / request magic link
- auth / confirm magic link
- auth / forgot password
- profile / update
- profile / avatar upload
- tickets / list
- tickets / create
- tickets / show
- tickets / update
- tickets / status update
- teams / members
- teams / role update
- teams / statuses CRUD
- teams / intake-links CRUD
- teams / invitation links CRUD

Make the API respect permissions strictly.

==================================================
UI / UX REQUIREMENTS
==================================================

Public home page should explain what TICKETHO can do:
- team-based ticketing
- simple onboarding
- custom statuses
- reporter intake links
- mobile-friendly usage
- easy future integration
- email/SMS notification groundwork
- educational Basil demo value

Please explicitly mention it is free and provided by the Syndorela Kingdom educational initiative.
Include a visible link to Syndorela.com.

Add a “Coming Soon” section with a nice list such as:
- custom ticket intake forms per team
- ticket comments and discussion threads
- file attachments
- assignment to staff members
- watchers / followers
- notification reply support
- Twilio SMS replies that update tickets
- email reply-to-ticket threading
- audit logs
- dashboard analytics
- dark mode
- embeddable mini-pages / iframe integrations
- webhooks
- richer public intake branding per team
- SLA / priority rules
- API tokens for external apps

Make the landing page feel generous and inviting.

==================================================
TEAM ADMIN FEATURES
==================================================

Team admins should be able to:
- create/manage team-specific intake URLs
- copy/share those URLs
- view who joined through those links if practical
- manage members
- promote reporter -> member
- manage statuses
- manage tickets
- see team ticket list
- configure notification provider placeholders
- invite users via standard team invitations too

==================================================
TICKET RULES
==================================================

Reporter:
- can create tickets
- can view only their own tickets
- should not see other team tickets
- should not be able to edit most tickets after submission, unless you decide to allow very minimal immediate edits before staff action
- read-only own ticket detail is fine

Member/admin/owner:
- can view team tickets according to role
- can edit/update statuses
- can work tickets normally

Use sane default statuses from the starter spec:
- Pending
- Approved
- Declined
- Completed
- On Hold

Allow team custom statuses too.

==================================================
SECURITY / VALIDATION
==================================================

Please implement solid basics:
- auth check on protected pages
- CSRF protection consistent with repo conventions
- permission checks per route/action
- secure random tokens for magic links/intake links/invitations
- expiration / single-use behavior where appropriate
- input validation
- upload validation for avatars
- safe file naming/storage
- team scoping on every ticket query
- reporter scoping to own tickets only

==================================================
REUSE / EDUCATIONAL VALUE
==================================================

Please keep the code educational and easy to inspect.
Use <?basil ?> templating on pages where it makes sense.
Show good examples of:
- loops
- conditional rendering
- partial includes
- form handling
- API-backed progressive enhancement
- role-aware UI rendering

This demo should be something we can point to later as:
“Here is a proper team app built in Basil.”

==================================================
DELIVERABLES
==================================================

Please implement the actual demo, not just notes.

I want:
1. Working Basil pages in /demos/ticketho
2. Routing wired up
3. DB migration(s) / seed(s)
4. Updated .env.example or equivalent config docs
5. Reusable layout/partials
6. Public home page
7. Auth/account flows
8. Intake + auto-login confirmation flow
9. Team admin pages
10. Ticket CRUD basics
11. Reporter role restrictions
12. Avatar upload support
13. README for this demo explaining setup and flow
14. Sample seed/demo data if helpful

==================================================
README / DOCS
==================================================

Please include a README for the demo covering:
- what TICKETHO is
- how to run it
- required .env variables
- DEFAULT_TEAM_ID behavior
- how team-specific intake URLs work
- how reporter onboarding works
- how to test the email confirmation -> auto-login -> create ticket flow
- avatar upload notes
- what is intentionally simplified because this is a demo
- future extensibility ideas

==================================================
IMPLEMENTATION PRIORITIES
==================================================

Please prioritize in this order:
1. app skeleton based on /demos/website
2. migrations/schema
3. auth/account/profile basics
4. default team seed + .env config
5. public intake registration flow
6. email confirmation auto-login link
7. create ticket flow
8. reporter restrictions
9. team admin pages
10. statuses/intake link management
11. polish landing page and coming soon section

==================================================
FINAL STYLE NOTE
==================================================

Make it feel clean, thoughtful, and surprisingly complete for a demo.
This should look like a free product from a whimsical but capable software kingdom.
Not silly, not corporate, not sterile — somewhere between “helpful startup landing page” and “clever demo app.”

Please inspect /demos/website first, follow the repo’s established patterns, and then build this as a proper Basil demo.