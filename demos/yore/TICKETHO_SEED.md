Junie —

Please add friendly demo seed data for TICKETHO so the app feels alive immediately after setup. This is demo/dev seed data only.

Use the following content as the basis for seed records. You may tweak field names to match the actual schema you build, but keep the spirit, relationships, and tone.

IMPORTANT:
- Seed data should be safe, fake, and obviously fictional.
- Use a single shared demo password for local/dev accounts only.
- Mark most seeded users as email-verified so the demo is easy to explore.
- Keep one or two users pending/unverified if useful for testing the confirmation flow.
- Make sure the default team exists and is easy to spot in the UI.
- Make sure at least one reporter belongs to each main team.
- Include a few tickets in different statuses.
- Include at least one ticket in the default team created through the generic intake path.
- Include at least one team-specific intake link per major team.

Suggested shared demo password:
DemoPass123!

Suggested DEFAULT_TEAM_ID:
1

==================================================
DEMO USERS
==================================================

$demo_users = [
[
"id" => 1,
"name" => "Queen Codelia",
"email" => "codelia@ticketho.demo",
"phone" => "555-0101",
"role_hint" => "system-owner-default-team-owner",
"avatar" => null,
"email_verified" => true
],
[
"id" => 2,
"name" => "Sir Patchwell",
"email" => "patchwell@ticketho.demo",
"phone" => "555-0102",
"role_hint" => "team-admin",
"avatar" => null,
"email_verified" => true
],
[
"id" => 3,
"name" => "Lady Queue",
"email" => "lady.queue@ticketho.demo",
"phone" => "555-0103",
"role_hint" => "team-admin",
"avatar" => null,
"email_verified" => true
],
[
"id" => 4,
"name" => "Milo Metrics",
"email" => "milo@ticketho.demo",
"phone" => "555-0104",
"role_hint" => "member",
"avatar" => null,
"email_verified" => true
],
[
"id" => 5,
"name" => "Penny Lantern",
"email" => "penny@ticketho.demo",
"phone" => "555-0105",
"role_hint" => "member",
"avatar" => null,
"email_verified" => true
],
[
"id" => 6,
"name" => "Ned Clipboard",
"email" => "ned@ticketho.demo",
"phone" => "555-0106",
"role_hint" => "member",
"avatar" => null,
"email_verified" => true
],
[
"id" => 7,
"name" => "Rita Reporter",
"email" => "rita@ticketho.demo",
"phone" => "555-0107",
"role_hint" => "reporter",
"avatar" => null,
"email_verified" => true
],
[
"id" => 8,
"name" => "Tommy Troubleticket",
"email" => "tommy@ticketho.demo",
"phone" => "555-0108",
"role_hint" => "reporter",
"avatar" => null,
"email_verified" => true
],
[
"id" => 9,
"name" => "Gloria Generic",
"email" => "gloria@ticketho.demo",
"phone" => "555-0109",
"role_hint" => "reporter-default-team",
"avatar" => null,
"email_verified" => true
],
[
"id" => 10,
"name" => "Felix Followup",
"email" => "felix@ticketho.demo",
"phone" => "555-0110",
"role_hint" => "recent-reporter",
"avatar" => null,
"email_verified" => false
],
[
"id" => 11,
"name" => "Ava Intake",
"email" => "ava@ticketho.demo",
"phone" => "555-0111",
"role_hint" => "promotable-reporter",
"avatar" => null,
"email_verified" => true
],
[
"id" => 12,
"name" => "Basil Builder",
"email" => "basil.builder@ticketho.demo",
"phone" => "555-0112",
"role_hint" => "owner-admin-helper",
"avatar" => null,
"email_verified" => true
]
];

==================================================
DEMO TEAMS
==================================================

$demo_teams = [
[
"id" => 1,
"name" => "Syndorela Support Desk",
"slug" => "syndorela-support",
"owner_user_id" => 1,
"is_default" => true,
"description" => "Default destination for generic intake and general support tickets."
],
[
"id" => 2,
"name" => "Clocktower Repairs",
"slug" => "clocktower-repairs",
"owner_user_id" => 2,
"is_default" => false,
"description" => "A busy team handling repairs, requests, and practical maintenance work."
],
[
"id" => 3,
"name" => "Lantern Watch",
"slug" => "lantern-watch",
"owner_user_id" => 3,
"is_default" => false,
"description" => "A team that watches incoming issues, triages them, and keeps things moving."
]
];

==================================================
TEAM MEMBERSHIPS
==================================================

$demo_team_members = [
[ "team_id" => 1, "user_id" => 1, "role" => "owner" ],
[ "team_id" => 1, "user_id" => 12, "role" => "admin" ],
[ "team_id" => 1, "user_id" => 9, "role" => "reporter" ],
[ "team_id" => 1, "user_id" => 10, "role" => "reporter" ],

    [ "team_id" => 2, "user_id" => 2, "role" => "owner" ],
    [ "team_id" => 2, "user_id" => 4, "role" => "admin" ],
    [ "team_id" => 2, "user_id" => 5, "role" => "member" ],
    [ "team_id" => 2, "user_id" => 7, "role" => "reporter" ],
    [ "team_id" => 2, "user_id" => 11, "role" => "reporter" ],

    [ "team_id" => 3, "user_id" => 3, "role" => "owner" ],
    [ "team_id" => 3, "user_id" => 6, "role" => "admin" ],
    [ "team_id" => 3, "user_id" => 12, "role" => "member" ],
    [ "team_id" => 3, "user_id" => 8, "role" => "reporter" ]
];

==================================================
GLOBAL DEFAULT STATUSES
==================================================

$global_statuses = [
[ "name" => "Pending", "color" => "#f5b700", "team_id" => null ],
[ "name" => "Approved", "color" => "#2e9d57", "team_id" => null ],
[ "name" => "Declined", "color" => "#d64545", "team_id" => null ],
[ "name" => "Completed", "color" => "#2d7ff9", "team_id" => null ],
[ "name" => "On Hold", "color" => "#4aa3a2", "team_id" => null ]
];

==================================================
TEAM-SPECIFIC CUSTOM STATUSES
==================================================

$team_statuses = [
[ "team_id" => 2, "name" => "Awaiting Parts", "color" => "#7b61ff" ],
[ "team_id" => 2, "name" => "Scheduled Visit", "color" => "#ff8a3d" ],
[ "team_id" => 3, "name" => "Needs Triage", "color" => "#8c52ff" ],
[ "team_id" => 3, "name" => "Watching", "color" => "#5b8def" ]
];

==================================================
PUBLIC INTAKE LINKS
==================================================

$public_intake_links = [
[
"team_id" => 1,
"label" => "General Support",
"token" => "default-support-demo",
"slug" => "general-support",
"active" => true,
"created_by" => 1,
"description" => "Generic support intake that lands in the default team."
],
[
"team_id" => 2,
"label" => "Clocktower Repair Requests",
"token" => "clocktower-repairs-demo",
"slug" => "clocktower-help",
"active" => true,
"created_by" => 2,
"description" => "Public intake link for repair and maintenance requests."
],
[
"team_id" => 2,
"label" => "Urgent Clocktower Issues",
"token" => "clocktower-urgent-demo",
"slug" => "clocktower-urgent",
"active" => true,
"created_by" => 2,
"description" => "A more urgent-looking intake path for demo purposes."
],
[
"team_id" => 3,
"label" => "Lantern Watch Intake",
"token" => "lantern-watch-demo",
"slug" => "lantern-watch",
"active" => true,
"created_by" => 3,
"description" => "Entry point for the Lantern Watch team."
]
];

==================================================
STANDARD TEAM INVITATION LINKS
==================================================

$team_invitations = [
[
"team_id" => 2,
"sender_user_id" => 2,
"token" => "invite-clocktower-member-demo",
"email" => null,
"role_hint" => "member",
"active" => true
],
[
"team_id" => 3,
"sender_user_id" => 3,
"token" => "invite-lantern-admin-demo",
"email" => "new.admin@ticketho.demo",
"role_hint" => "admin",
"active" => true
]
];

==================================================
DEMO TICKETS
==================================================

$demo_tickets = [
[
"team_id" => 1,
"reporter_user_id" => 9,
"title" => "General support question about ticket visibility",
"description" => "I submitted a request earlier and wanted to confirm that I can come back later and still see it from my account dashboard.",
"status_name" => "Pending",
"notes" => "Created through generic/default intake flow.",
"estimate" => "15m",
"time_spent" => "0m"
],
[
"team_id" => 1,
"reporter_user_id" => 10,
"title" => "Trouble confirming my email link",
"description" => "The first confirmation link expired while I was distracted. I would like a fresh link and to continue the intake flow.",
"status_name" => "On Hold",
"notes" => "Useful for testing pending verification / resend behavior.",
"estimate" => "10m",
"time_spent" => "5m"
],
[
"team_id" => 2,
"reporter_user_id" => 7,
"title" => "Clocktower west stair lantern keeps flickering",
"description" => "The lantern near the west stair landing blinks every few seconds and sometimes goes dark entirely at night.",
"status_name" => "Awaiting Parts",
"notes" => "Team-specific status example.",
"estimate" => "45m",
"time_spent" => "20m"
],
[
"team_id" => 2,
"reporter_user_id" => 11,
"title" => "Handrail on upper maintenance platform feels loose",
"description" => "The rail does not seem dangerous yet, but it definitely shifts when leaned on and should be checked soon.",
"status_name" => "Scheduled Visit",
"notes" => "Good example of a promotable reporter having an active ticket.",
"estimate" => "1h",
"time_spent" => "15m"
],
[
"team_id" => 2,
"reporter_user_id" => 7,
"title" => "Small draft coming through window latch in bell room",
"description" => "Cold air is getting in around the latch and causing the room to feel damp by morning.",
"status_name" => "Approved",
"notes" => "Simple approved ticket for the list view.",
"estimate" => "20m",
"time_spent" => "10m"
],
[
"team_id" => 3,
"reporter_user_id" => 8,
"title" => "Need help understanding which team link to use",
"description" => "I arrived through one intake page but was not sure whether my request belonged to Lantern Watch or the default support desk.",
"status_name" => "Needs Triage",
"notes" => "Useful for demonstrating team triage decisions.",
"estimate" => "15m",
"time_spent" => "5m"
],
[
"team_id" => 3,
"reporter_user_id" => 8,
"title" => "Recurring issue seems resolved but please keep an eye on it",
"description" => "The original issue has calmed down for now, but I would still like the team to monitor it for another day or two.",
"status_name" => "Watching",
"notes" => "Demonstrates another custom team status.",
"estimate" => "30m",
"time_spent" => "12m"
],
[
"team_id" => 3,
"reporter_user_id" => 8,
"title" => "Request closed after follow-up",
"description" => "Everything looks good now. Thank you for the help.",
"status_name" => "Completed",
"notes" => "Closed/completed example for filtering and counts.",
"estimate" => "10m",
"time_spent" => "10m"
]
];

==================================================
OPTIONAL TICKET COMMENTS / ACTIVITY PLACEHOLDERS
==================================================

$demo_ticket_activity = [
[
"ticket_title" => "Clocktower west stair lantern keeps flickering",
"entries" => [
"Reporter submitted ticket through team-specific intake link.",
"Admin reviewed request and set custom status to Awaiting Parts.",
"Replacement lantern glass requested from stores."
]
],
[
"ticket_title" => "Need help understanding which team link to use",
"entries" => [
"Reporter confirmed email and entered via Lantern Watch intake page.",
"Admin noted possible routing confusion and kept ticket in triage."
]
]
];

==================================================
OPTIONAL TEAM SETTINGS / PROVIDER PLACEHOLDERS
==================================================

$demo_team_settings = [
[
"team_id" => 2,
"provider_type" => "email",
"provider_name" => "smtp",
"config_note" => "Demo SMTP placeholder enabled for Clocktower Repairs"
],
[
"team_id" => 2,
"provider_type" => "sms",
"provider_name" => "twilio",
"config_note" => "Demo Twilio placeholder for future notification support"
],
[
"team_id" => 3,
"provider_type" => "email",
"provider_name" => "ses",
"config_note" => "Demo SES placeholder for Lantern Watch"
]
];

==================================================
OPTIONAL MAGIC-LINK / TOKEN TEST RECORDS
==================================================

$demo_magic_link_context = [
[
"email" => "felix@ticketho.demo",
"purpose" => "intake_confirm",
"team_id" => 1,
"notes" => "Useful if you want one visible pending confirmation scenario in dev."
],
[
"email" => "ava@ticketho.demo",
"purpose" => "login",
"team_id" => 2,
"notes" => "Useful for testing return-to-ticket or magic-login UI."
]
];

==================================================
SEEDING BEHAVIOR NOTES
==================================================

Please implement the seeding with these behaviors:

1. Create teams first in stable order so:
    - team 1 = Syndorela Support Desk
    - team 2 = Clocktower Repairs
    - team 3 = Lantern Watch

2. Set .env.example to include:
   DEFAULT_TEAM_ID=1

3. Seed the shared demo password for all users, hashed properly through the real auth code path.

4. Mark most accounts verified.
   Optionally leave Felix Followup unverified to help test the confirmation path.

5. If the schema supports avatars, leave them null by default.

6. Make sure seeded tickets resolve the proper status IDs by name rather than relying on hard-coded status IDs.

7. If you support soft deletion, keep all demo records active.

8. If the app supports a team switcher, make Basil Builder belong to multiple teams so that screen can be demonstrated.

9. Include clear comments in the seed code explaining which records exist for which UI/demo scenario.

==================================================
SUGGESTED LOGIN CHEAT SHEET FOR README
==================================================

Please also add a small section in the README like this:

Demo accounts:
- codelia@ticketho.demo — default team owner
- patchwell@ticketho.demo — Clocktower Repairs owner
- lady.queue@ticketho.demo — Lantern Watch owner
- rita@ticketho.demo — reporter in Clocktower Repairs
- tommy@ticketho.demo — reporter in Lantern Watch
- gloria@ticketho.demo — reporter in default team

Shared demo password:
DemoPass123!

==================================================
OPTIONAL UI HELPERS
==================================================

If helpful, surface a few of these demo values in the UI:
- Default team badge on Syndorela Support Desk
- Intake link labels visible on admin pages
- Reporter role badge
- One “promote to member” action for Ava Intake
- Team-specific status colors on ticket list and detail screens

==================================================
GOAL
==================================================

I want the seeded demo to feel immediately explorable:
- admins have something to manage
- reporters have something to see
- intake links exist
- custom statuses exist
- team switching can be demonstrated
- the default team behavior is obvious
- the app does not feel empty on first run


And here’s a tiny bonus snippet with a compact Basil/PHP-style array shape Junie can mirror if she wants a simple seed helper structure:

<?php

$demo_users = [
    [
        "name" => "Queen Codelia",
        "email" => "codelia@ticketho.demo",
        "phone" => "555-0101",
        "password" => "DemoPass123!",
        "email_verified" => true,
    ],
    [
        "name" => "Sir Patchwell",
        "email" => "patchwell@ticketho.demo",
        "phone" => "555-0102",
        "password" => "DemoPass123!",
        "email_verified" => true,
    ],
];

$demo_teams = [
    [
        "name" => "Syndorela Support Desk",
        "slug" => "syndorela-support",
        "owner_email" => "codelia@ticketho.demo",
        "is_default" => true,
    ],
    [
        "name" => "Clocktower Repairs",
        "slug" => "clocktower-repairs",
        "owner_email" => "patchwell@ticketho.demo",
        "is_default" => false,
    ],
];


Suggested demo intake URLs:

/intake
/intake/general-support
/intake/clocktower-help
/intake/clocktower-urgent
/intake/lantern-watch

