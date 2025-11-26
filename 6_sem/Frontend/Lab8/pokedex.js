const pokemonListElement = document.getElementById("pokemonList");
  const loadingElement = document.getElementById("loading");
  const errorElement = document.getElementById("errorText");
  const contentElement = document.getElementById("pokemonDetails");

  const nameElement = document.getElementById("pokemonName");
  const imgElement = document.getElementById("pokemonImg");
  const typesElement = document.getElementById("pokemonTypes");
  const statsElement = document.getElementById("pokemonStats");
  const flavorTextElement = document.getElementById("pokemonFlavorText");

  const API_BASE = "https://pokeapi.co/api/v2/";

  function showLoading() {
    loadingElement.style.display = "block";
    errorElement.style.display = "none";
    contentElement.style.display = "none";
  }

  function showError() {
    loadingElement.style.display = "none";
    errorElement.style.display = "block";
    contentElement.style.display = "none";
  }

  function showContent() {
    loadingElement.style.display = "none";
    errorElement.style.display = "none";
    contentElement.style.display = "flex";
  }

  async function preloadImage(src) {
    const img = new Image();
    img.src = src;
    await img.decode();
    return img;
  }

  function cleanFlavorText(text) {
    return text.replace(/[\n\f]/g, " ")
    .replace(/\u00ad\n/g, "")
    .replace(/\u00ad/g, "")
    .replace(/ -\n/g, " - ")
    .replace(/-\n/g, "-");
  }

  async function fetchPokemonList() {
    showLoading();
    try {
      const response = await fetch(`${API_BASE}pokemon-species?limit=151`);
      const data = await response.json();
      pokemonListElement.innerHTML = "";
      data.results.forEach(pokemon => {
        const li = document.createElement("li");
        li.textContent = capitalize(pokemon.name);
        li.addEventListener("click", () => fetchPokemonData(pokemon.name));
        pokemonListElement.appendChild(li);
      });
      loadingElement.style.display = "none";
    } catch (err) {
      showError();
    }
  }

  function capitalize(str) {
    return str.charAt(0).toUpperCase() + str.slice(1);
  }

  async function fetchPokemonData(name) {
    showLoading();
    try {
      const speciesRes = await fetch(`${API_BASE}pokemon-species/${name}`);
      const speciesData = await speciesRes.json();

      const variety = speciesData.varieties.find(v => v.is_default);
      const pokemonRes = await fetch(variety.pokemon.url);
      const pokemonData = await pokemonRes.json();

      // Preload image
      const img = await preloadImage(pokemonData.sprites.front_default);

      // Name
      nameElement.textContent = capitalize(speciesData.name);

      // Image
      imgElement.src = img.src;
      imgElement.alt = speciesData.name;

      // Types
      typesElement.innerHTML = "";
      pokemonData.types.forEach(t => {
        const span = document.createElement("span");
        span.className = "type";
        span.textContent = capitalize(t.type.name);
        typesElement.appendChild(span);
      });

      // Stats
      statsElement.innerHTML = "";
      pokemonData.stats.forEach(stat => {
        const statDiv = document.createElement("div");
        statDiv.className = "stat";

        const nameSpan = document.createElement("span");
        nameSpan.textContent = capitalize(stat.stat.name.replace("-", " "));

        const valueSpan = document.createElement("span");
        valueSpan.textContent = stat.base_stat;

        statDiv.appendChild(nameSpan);
        statDiv.appendChild(valueSpan);
        statsElement.appendChild(statDiv);
      });

      // Flavor Text
      const flavor = speciesData.flavor_text_entries.find(
        entry => entry.language.name === "en"
      );
      flavorTextElement.textContent = flavor ? cleanFlavorText(flavor.flavor_text) : "No description available.";

      showContent();
    } catch (err) {
      showError();
    }
  }

  fetchPokemonList();