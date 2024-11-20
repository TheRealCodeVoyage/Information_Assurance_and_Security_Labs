document.addEventListener("DOMContentLoaded", function () {
    document.querySelectorAll("pre > code").forEach((codeBlock) => {
        const button = document.createElement("button");
        button.innerText = "Copy";
        button.className = "copy-button";

        button.addEventListener("click", () => {
            navigator.clipboard.writeText(codeBlock.textContent).then(() => {
                button.innerText = "Copied!";
                setTimeout(() => (button.innerText = "Copy"), 2000);
            });
        });

        const pre = codeBlock.parentNode;
        pre.style.position = "relative";
        button.style.position = "absolute";
        button.style.top = "5px";
        button.style.right = "5px";

        pre.appendChild(button);
    });
});
