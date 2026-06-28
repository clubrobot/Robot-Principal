FROM python:3.14-trixie
LABEL authors="awing"

RUN python3 -m pip install -U platformio
RUN mkdir -p /etc/udev/rules.d/
RUN curl https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | tee /etc/udev/rules.d/99-platformio-udev.rules

WORKDIR /project

ENTRYPOINT ["pio", "run"]