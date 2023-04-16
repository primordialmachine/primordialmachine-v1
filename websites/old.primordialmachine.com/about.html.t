@{ pageTitle = "About Me" }
@{ pageDescription = "Primordial Machine - About Me." }
@{ pageLanguage = "en" }
@{ parentLink = "" }

@(> "./templates/_header.html.t")

<main>
<nav>
<a href="@(hostname)">Home</a> &rangle; <a href="@(hostname)">About</a>
</nav>
<h1>Primordial Machine :: About</h1>
<p>
Primordial Machine is an avatar of mine and the name of this website.
</p>

<faq>
  <faq-q>
  Who are you?
  </faq-q>
  <faq-a>
  My name is Michael Heilmann.
  I am a software architect.
  </faq-a>
  
  <faq-q>
  What is software architecture?
  </faq-q>
  <faq-a>
  The planned
  No this site is about me.
  As I am considered as a software architect, certainly, software architecture comes into play.
  </faq-a>
  
  <faq-q>
  Is this site about software architecture?
  </faq-q>
  <faq-a>
  No this site is about me.
  As I am considered as a software architect, certainly, software architecture comes into play.
  </faq-a>
  
  <faq-q>
  What is Primordial Machine?
  </faq-q>
  <faq-a>
  Primordial Machine is an avatar of mine.
  Primordial Machine is the name of this website.
  </faq-a>
  
  <faq-q>
  Where does the name Primordial Machine come from?
  </faq-q>
  <faq-a>
  The name of this website Primordial Machine is a reference to a recurring wording from an extracurricular work of mine. I used the term Machine as an abbreviation for model of a computing machine. That work also developed different machines based on each other. The machine which was the common origin of all these machines consequently was called the Primordial Machine.
  </faq-a>
  
  <faq-q>
  What typefaces does this website use?
  </faq-q>
  <faq-a>
  This website uses <a href="https://fonts.google.com/specimen/Crimson+Text">Crimson Text</a>
  designed by Sebastian Kosch and others for body texts and some navigation elements.
  It uses <a href="https://fonts.google.com/specimen/Fira+Sans">Fira Sans</a>
  for headlines and some navigation elements.
  </faq-a>
</faq>

</main>

@(> "./templates/_footer.html.t")
