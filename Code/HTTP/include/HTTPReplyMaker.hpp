#pragma once

namespace AxxonsoftInternProject
{
	namespace http
	{
		enum ReplyType
		{
            ok = 200,
            created = 201,
            accepted = 202,
            no—ontent = 204,
            multiple—hoices = 300,
            movedPermanently = 301,
            movedTemporarily = 302,
            notModified = 304,
            badRequest = 400,
            unauthorized = 401,
            forbidden = 403,
            notFound = 404,
            internalServer_error = 500,
            notImplemented = 501,
            badGateway = 502,
            serviceUnavailable = 503
		};

		class HTTPReplyMaker
		{

		};

	}
}