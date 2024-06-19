from django.shortcuts import render


from django.http import HttpResponse, JsonResponse
import os
from PIL import Image
from fruit import fruit_model


def index(request):
    return render(request, "index.html")


def classify(request):
    path = './fruit/static/fruit/file/'
    dicts = {}
    if request.method == "POST":
        img = request.FILES.get("image")
        file = open(path + "image.jpg", 'wb+')
        for chunk in img.chunks():
            file.write(chunk)
        file.close()
        dicts = fruit_model.predict(path)
        return JsonResponse(dicts)
    else:
        return HttpResponse("Method Should Be POST !")
