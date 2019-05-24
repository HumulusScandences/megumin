# -*- coding: utf-8 -*-

import os
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
import time
import datetime


def gen(list):

    text = list[0]

    im = Image.new("RGB", (300, 50), (255, 255, 255))
    dr = ImageDraw.Draw(im)
    font = ImageFont.truetype(os.path.join("fonts", "C:\Users\Administrator\Desktop\mytf.ttf"), 14)

    dr.text((10, 5), text, font=font, fill="#000000")

    im.show()
    im.save(time.time()+".png")
