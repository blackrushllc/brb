# TICKETHO - Team Intake & Ticket Management Demo

TICKETHO is a lightweight, team-based ticket management platform built as an educational demo for the Basil templating language and app logic. It is part of the Syndorela Kingdom educational initiative.

## Features

- **Team-Based Tickets**: Organize work by team.
- **Guided Reporter Onboarding**: A unique intake flow that confirms email and logs users in automatically.
- **Public Intake Links**: Team admins can generate specific URLs for reporters.
- **Role-Based Access**: Owner, Admin, Member, and Reporter roles.
- **Custom Statuses**: Teams can define their own ticket workflows.
- **Profile Management**: User profile editing and avatar uploads.
- **Mobile Friendly**: Clean, responsive UI.

## How it Works (Intake Flow)

1. A visitor arrives at a team's intake page (e.g., `intake.basil?token=...`).
2. They enter their name and email.
3. The system generates a secure, time-limited magic link and "emails" it to them (shown on screen in this demo).
4. Clicking the link confirms the email, logs the user in, joins them to the team as a **Reporter**, and lands them directly on the **New Ticket** form.
5. Reporters can later return to view only their own tickets.

## Setup & Configuration

### Environment Variables (.env)

The application uses a `.env` file for configuration:

- `DEFAULT_TEAM_ID`: The ID of the team used for generic intake (defaults to 1).
- `SYSTEM_OWNER_ID`: The ID of the seeded system owner (defaults to 1).

### Database

The application uses SQLite (`ticketho.db`). The schema is automatically initialized and seeded on first run.

### Running the Demo

1. Ensure the `brb` server is running.
2. Navigate to `/demos/ticketho/index.basil` in your browser.
3. To test the intake flow, click "Submit a Ticket" on the home page or use a team admin to generate a specific link.

## Technical Details

- **Basil Templating**: Uses `<?basil ?>` for loops, conditionals, and partial includes.
- **CGI Integration**: Leverages `CGI_HAS_FILE%` and other CGI-specific functions for form handling and file uploads.
- **Schema**: Tables for `users`, `teams`, `team_members`, `tickets`, `statuses`, `public_intake_links`, and `email_login_tokens`.

## Implementation Notes

- **Password Security**: For demo simplicity, passwords are stored in plain text. In a production app, use proper hashing.
- **Email Simulation**: Since this is a demo, the "magic link" is displayed on the screen instead of being sent via a real SMTP server.
- **Avatar Resizing**: Image uploads are saved directly. Server-side resizing would require an external library or a more advanced Basil module.

## Future Ideas

- Custom ticket intake forms per team.
- Ticket comments and discussion threads.
- File attachments for tickets.
- Assignment to staff members.
- Dashboard analytics and audit logs.
- Dark mode support.
