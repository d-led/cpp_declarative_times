Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/trusty64"
  config.vm.provision "shell", privileged: false, inline: <<-SHELL
    sudo apt-get -y install git build-essential
    ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Linuxbrew/install/master/install)"
    export PATH="$HOME/.linuxbrew/bin:$PATH"
    echo 'export PATH="$HOME/.linuxbrew/bin:$PATH"' >>~/.bash_profile
    brew install gcc cmake
    echo cd /vagrant >> `pwd`/.bash_profile
  SHELL

  config.vm.provider "virtualbox" do |v|
    v.memory = 2048
    v.cpus = 2
  end
end
