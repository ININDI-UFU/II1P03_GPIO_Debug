# Instrumentação Industrial I
## Aula Prática 02: Trabalhando com GitHub e PlatformIO no VSCode com ESP32

### Introdução

Este projeto explora o uso integrado do GitHub, Visual Studio Code (VSCode) e PlatformIO para o desenvolvimento de aplicações com ESP32. Essa combinação de ferramentas facilita o controle de versão, a colaboração em equipe e o desenvolvimento eficiente para microcontroladores. Aqui estão algumas informações importantes sobre as ferramentas utilizadas:

#### GitHub
O GitHub é uma plataforma poderosa para controle de versão e colaboração em projetos. Ele permite:
- Gerenciar código fonte com Git.
- Colaborar em equipe com pull requests e revisões de código.
- Acompanhar o histórico de alterações do projeto.

Com a integração do GitHub no VSCode, é possível realizar operações como commits, push, pull, criação de branches e análise de pull requests diretamente no editor.

#### Visual Studio Code (VSCode)
O VSCode é um editor de código-fonte leve e altamente extensível que suporta diversas linguagens e ferramentas. Com extensões como PlatformIO IDE e GitHub, ele se torna uma poderosa estação de trabalho para desenvolvedores de microcontroladores.

Funcionalidades principais:
- Depuração integrada.
- Controle de versão com Git e GitHub.
- Suporte a extensões como GitLens, GitHub Pull Requests and Issues e PlatformIO.

#### PlatformIO
O PlatformIO é um ambiente de desenvolvimento integrado (IDE) que facilita o desenvolvimento para microcontroladores, como o ESP32. Ele oferece:
- Gerenciamento simplificado de bibliotecas e dependências.
- Ferramentas de construção, upload e depuração.
- Suporte a múltiplos frameworks, incluindo Arduino e ESP-IDF.

### Materiais

#### Software
- Visual Studio Code.
- Extensões: PlatformIO IDE, GitHub Pull Requests and Issues, GitLens.
- Drivers USB para ESP32.

#### Hardware
- Placa ESP32.
- Cabo USB.

### Procedimento Experimental

#### 1. Preparação do Ambiente
1. **Instalando o Python**:
   - Veja o video de como proceder com a instalação correta do python:
   [![Assista ao Vídeo](https://img.youtube.com/vi/CF1MhdQCnfc/hqdefault.jpg)](https://www.youtube.com/watch?v=CF1MhdQCnfc)
2. **Instalar o VSCode**:
   - Baixe e instale o VSCode conformo vídeo abaixo: 
   [![Assista ao Vídeo](https://img.youtube.com/vi/FOqKMPX6BMo/hqdefault.jpg)](https://www.youtube.com/watch?v=FOqKMPX6BMo)
3. **Adicionar Extensões**:
   - Instale as extensões PlatformIO IDE, GitHub Pull Requests and Issues e GitLens.
4. **Configurar GitHub no VSCode**:
   - Faça login no GitHub utilizando a extensão GitHub Pull Requests and Issues.
5. **Instalar o PlatformIO**:
   - Após instalar a extensão, reinicie o VSCode para concluir a configuração.

#### 2. Criação de Projetos
1. **Criar um Projeto no PlatformIO**:
   - Configure o projeto para usar ESP32 Dev Module com o framework Arduino.
2. **Testar o Projeto**:
   - Substitua o código no arquivo `src/main.cpp` pelo exemplo fornecido e faça o upload para o ESP32. O video abaixo demostra isso:  
   [![Assista ao Vídeo](https://img.youtube.com/vi/HSSXU4XHBYY/hqdefault.jpg)](https://www.youtube.com/watch?v=HSSXU4XHBYY)

#### 3. Integração com GitHub
- Utilize o Git integrado ao VSCode para:
  - Criar um repositório no GitHub.
  - Fazer commits e sincronizar o código.
  - Criar branches e pull requests.

O video abaixo apresenta como fazer tudo isso:  
[![Assista ao Vídeo](https://img.youtube.com/vi/B_RTIOYZmvw/hqdefault.jpg)](https://www.youtube.com/watch?v=B_RTIOYZmvw)

#### 4. Observações importantes
- Veja o video abaixo para que os processos interativos entre o github e vscode funcionem adequadamente.
[![Assista ao Vídeo](https://img.youtube.com/vi/6QpcVrRDbp4/hqdefault.jpg)](https://www.youtube.com/watch?v=6QpcVrRDbp4)

#### 5. Atualizações e Colaboração
1. **Trabalhar em Equipe**:
   - Utilize pull requests para revisar e integrar código.
2. **Adicionar `.gitignore`**:
   - Inclua os diretórios `.vscode/` e `.pio/` para evitar arquivos temporários no repositório.

### Tratamento e Análise
- Teste o código no ESP32 e analise os logs no PlatformIO.
- Verifique se o repositório GitHub está atualizado.
- Utilize ferramentas do PlatformIO para debugar o código e validar a execução.

### Boas Práticas para Mensagens de Commit

Para garantir que seu projeto seja bem documentado e fácil de manter, siga estas práticas:
📌 Não pense que seu código é autoexplicativo: Se esforce para escrever uma mensagem que retrate de forma concisa exatamente o que aquela alteração significa.

📌 Especifique o tipo de commit: Utilize prefixos no assunto referente ao tipo de cada commit. 

    Ex:

        feat: uma nova feature (recurso) que você está adicionando a uma aplicação específica ;
        fix: a resolução de um bug;
        style: recurso e atualizações relacionadas à estilização;
        refactor: refatoração de uma seção específica da base de código;
        test: tudo o que for relacionado a testes;
        docs: tudo o que for relacionado à documentação;
        chore: manutenção regular do código. 

📌 Use um verbo no infinitivo: A mensagem do campo “Assunto” (primeira linha) deve iniciar a com um verbo no infinitivo que descreva a ação realizada (Ex: "Adicionar", "Corrigir" ou "Atualizar"), seguido por uma descrição concisa da mudança. Ex: "Adicionar validação de formulário para garantir que todos os campos obrigatórios sejam preenchidos".

📌 Mantenha-a curta e concisa: As mensagens de commit devem ser curtas e diretas, com no máximo 72 caracteres na primeira linha (assunto) e uma linha em branco após a primeira linha (descrição). Isso torna mais fácil para outros desenvolvedores entenderem rapidamente o que foi feito.

📌Forneça contexto: A segunda linha da mensagem deve fornecer um contexto adicional sobre o que foi feito. Por exemplo, se você estiver corrigindo um bug, descreva o problema resolvido.

📌 Mantenha-a clara e objetiva: Mantenha a mensagem clara e objetiva, sem usar jargões ou frases excessivamente técnicas. Isso ajuda a garantir que a mensagem seja compreendida por todos os membros da equipe.

📌 Use passos de ação se necessário: Se o commit requer muitos passos, inclua-os na mensagem de commit, separando-os com uma lista numerada ou com marcadores bullet. Isso ajuda a garantir que o processo seja claro e fácil de seguir.

Em geral, ao escrever uma mensagem de commit, pense na pessoa que estará lendo a mensagem muito tempo depois, quando as circunstâncias poderão ter mudado e a pessoa pode não ter conhecimento do contexto original. Dessa forma, mantenha a mensagem clara, objetiva e forneça o contexto necessário para ajudar outros desenvolvedores a entender rapidamente o que foi feito.

Mantenha essas práticas em mente ao trabalhar com o Git, e você verá que será mais fácil gerenciar e manter o código organizado e eficiente. 😉

## Tarefa a ser executada: 

- Faça um led piscar.
- A comunicação serial não pode parar. 
- Use o simulIDE para testar seu código.
- Não use delay no loop.

### Referências
- [Documentação do PlatformIO](https://platformio.org/)
- [Documentação do VSCode](https://code.visualstudio.com/docs)
- [Ajuda do GitHub](https://docs.github.com/)



