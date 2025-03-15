function atualizarDados() {
    fetch('/data')
        .then(response => response.json())
        .then(data => {
            document.getElementById('tensaoNoBarramento').innerText = data.tensaoNoBarramento + ' V';
            document.getElementById('tensaoNoShunt').innerText = data.tensaoNoShunt + ' mV';
            document.getElementById('tesaoNaCarga').innerText = data.tesaoNaCarga + ' V';
            document.getElementById('correnteDaCarga').innerText = data.correnteDaCarga + ' mA';
            document.getElementById('potenciaDaCarga').innerText = data.potenciaDaCarga + ' mW';
        })
        .catch(error => console.error('Erro ao buscar dados:', error));
}

setInterval(atualizarDados, 1000);
window.onload = atualizarDados;
