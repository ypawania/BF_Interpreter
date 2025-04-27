document.getElementById("run").addEventListener("click", async () => {
  const code = document.getElementById("code").value;
  const input = document.getElementById("input").value;
  try {
    const url = "http://localhost:18080/interprate";
    const response = await fetch(url, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ code: code, input: input }),
    });

    const data = await response.json();
    console.log(data);
    console.log(data.output);
    document.getElementById("output").innerText = data.output;

  }
  catch (error) { console.error("Error: ", error); }

})
